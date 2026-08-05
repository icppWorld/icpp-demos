"""Deploys & tests all canisters, each in its own local network.

icp-cli runs a local network per project, and every canister's `icp.yaml` asks
for an ephemeral gateway port (`gateway.port: 0`), so the canisters do not
collide and can be built, deployed and tested **in parallel**. Under dfx this
was impossible: there was a single global replica on a fixed port.

Use `--jobs 1` to fall back to running them one at a time, which produces a
simpler log when you are debugging a single canister.

Every canister is deployed with, and tested as, the identity named by
${ICPP_PRO_TEST_IDENTITY} - the Makefile creates it and exports it. The
machine-wide active identity (`icp identity default`) is never read and never
changed.
"""

import argparse
import os
import shutil
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from functools import partial
from pathlib import Path
from typing import List, Tuple

import typer
from icpp.run_shell_cmd import run_shell_cmd

SCRIPTS_PATH = Path(__file__).parent
ROOT_PATH = Path(__file__).parent.parent

# The identity to deploy with. A canister's controller is whoever deployed it,
# so the deploy and the tests must agree on it. pytest picks the same name up
# from this environment variable, which the Makefile exports.
IDENTITY_ENV_VAR = "ICPP_PRO_TEST_IDENTITY"

# Generous ceiling: a cold `icpp build-wasm` compiles the whole C++ tree.
# It matters that this is explicit - `run_shell_cmd` defaults to 30s whenever
# output is captured, which a build blows through.
TIMEOUT_SECONDS = 3600


class StepError(Exception):
    """A step of a canister's pipeline failed."""


def run_step(cmd: str, cwd: Path, log: List[str]) -> None:
    """Runs one command, appending its output to `log`. Raises on failure.

    Output is captured rather than streamed, so that parallel canisters do not
    interleave their logs into an unreadable mess.
    """
    log.append(f"$ {cmd}")
    try:
        out = run_shell_cmd(
            cmd, capture_output=True, cwd=cwd, timeout_seconds=TIMEOUT_SECONDS
        )
    except subprocess.CalledProcessError as e:
        log.append(e.output or "")
        raise StepError(cmd) from e

    log.append(out)
    # A timeout does NOT raise - run_shell_cmd returns this marker string
    # instead, which would otherwise read as success.
    if out.startswith("ERROR: Command") and "timed out" in out:
        raise StepError(cmd)


def network_stop(canister_path: Path) -> None:
    """Stops the canister's project-local network, if it is running.

    `icp network stop` exits non-zero when no network is running, which is not
    an error for us - we only want the network down afterwards.
    """
    try:
        run_shell_cmd(
            "icp network stop",
            capture_output=True,
            cwd=canister_path,
            timeout_seconds=TIMEOUT_SECONDS,
        )
    except subprocess.CalledProcessError:
        pass


def network_start_clean(canister_path: Path, log: List[str]) -> None:
    """Starts a clean, project-local network for the canister.

    icp-cli has no `--clean` flag. A managed network keeps both its replica
    state and its canister id mappings under `.icp/cache`, so removing that
    directory is the equivalent of `dfx start --clean`.

    NOTE: only `.icp/cache` - never `.icp`, which also holds `data/mappings/`
    with the mainnet canister ids.
    """
    network_stop(canister_path)
    shutil.rmtree(canister_path / ".icp" / "cache", ignore_errors=True)
    run_step("icp network start --background", canister_path, log)


def get_test_identity() -> str:
    """Returns the icp identity to deploy with, or exits with an explanation."""
    identity = os.environ.get(IDENTITY_ENV_VAR)
    if not identity:
        typer.echo(
            f"ERROR: ${IDENTITY_ENV_VAR} is not set.\n"
            f"It names the icp identity to deploy with and run the tests as. "
            f"icpp-pro never uses the machine-wide active identity.\n"
            f"Run this through `make all-canister-deploy-local-pytest`, which "
            f"creates & exports it, or set it yourself:\n"
            f"    icp identity new my-testing --storage plaintext\n"
            f"    export {IDENTITY_ENV_VAR}=my-testing"
        )
        sys.exit(1)
    return identity


def test_canister(canister_path: Path, identity: str) -> Tuple[str, bool, List[str]]:
    """Builds, deploys & tests one canister. Returns (name, ok, log)."""
    name = canister_path.name
    log: List[str] = [f"==== {name}"]
    test_api_path = canister_path / "test/test_apis.py"
    configs = [file.name for file in canister_path.glob("*.toml")]

    try:
        for config in configs:
            log.append(f"-- start a clean local network ({name})")
            network_start_clean(canister_path, log)

            log.append(f"-- build the wasm with config {config}")
            run_step(
                f"icpp build-wasm --config {config} --to-compile all",
                canister_path,
                log,
            )

            log.append(f"-- deploy {name}")
            run_step(
                f"icp deploy --environment local --yes --identity {identity}",
                canister_path,
                log,
            )

            # pytest runs from the canister directory: that is the icp project
            # root, which is how icp finds icp.yaml and this canister's network.
            # It needs no --identity flag: the subprocess inherits the exported
            # ${ICPP_PRO_TEST_IDENTITY}, so it runs as the same identity.
            log.append(f"-- pytest {test_api_path}")
            run_step(f"pytest --network=local {test_api_path}", canister_path, log)

            if name == "files":
                log.append("-- verify files persist across a canister upgrade")
                run_step(
                    f"icp deploy --environment local --yes --mode upgrade "
                    f"--identity {identity}",
                    canister_path,
                    log,
                )
                run_step(
                    f"pytest --network=local -m run_after_upgrade {test_api_path}",
                    canister_path,
                    log,
                )

            network_stop(canister_path)
        return name, True, log

    except StepError as e:
        log.append(f"!! FAILED: {e}")
        return name, False, log
    finally:
        # Never leave a replica running, whatever happened above.
        network_stop(canister_path)


def main() -> int:
    """Build, deploy & pytest every canister, in parallel by default."""
    canister_paths = sorted(
        p
        for p in (ROOT_PATH / "canisters").glob("*")
        if (p / "icp.yaml").exists()  # skips __pycache__ & friends
    )

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--jobs",
        type=int,
        default=min(len(canister_paths), os.cpu_count() or 1),
        help="how many canisters to build & test concurrently (1 = serial)",
    )
    args = parser.parse_args()
    jobs = max(1, args.jobs)

    # Resolved up front, so a missing identity is one clear error before
    # anything is built, rather than six failing deploys.
    identity = get_test_identity()

    typer.echo(
        f"Testing {len(canister_paths)} canisters as identity '{identity}' "
        f"with {jobs} job(s): {', '.join(p.name for p in canister_paths)}"
    )

    failed: List[str] = []
    with ThreadPoolExecutor(max_workers=jobs) as pool:
        for name, ok, log in pool.map(
            partial(test_canister, identity=identity), canister_paths
        ):
            # One block per canister, printed whole, so parallel logs stay readable.
            typer.echo("\n".join(log))
            typer.echo(f"---- {name}: {'PASSED' if ok else 'FAILED'}\n")
            if not ok:
                failed.append(name)

    if failed:
        typer.echo(f"--\nSomething did not pass: {', '.join(failed)}")
        return 1

    typer.echo("--\nCongratulations, everything passed!")
    try:
        typer.echo("💯 🎉 🏁")
    except UnicodeEncodeError:
        typer.echo(" ")
    return 0


if __name__ == "__main__":
    sys.exit(main())
