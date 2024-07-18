"""Deploys & tests all canisters in a freshly started local network"""

import sys
import platform
from pathlib import Path
import subprocess
import typer
from icpp.run_shell_cmd import run_shell_cmd
from icpp.run_dfx_cmd import run_dfx_cmd

SCRIPTS_PATH = Path(__file__).parent
ROOT_PATH = Path(__file__).parent.parent


def main() -> int:
    """Start local network; Deploy canister; Pytest"""
    canister_paths = list((ROOT_PATH / "canisters").glob("*"))
    for canister_path in canister_paths:  # pylint: disable=too-many-nested-blocks
        typer.echo(f"====\nTesting canister: {canister_path.name}")

        test_api_path = canister_path / "test/test_apis.py"
        configs = [file.name for file in canister_path.glob("*.toml")]
        for config in configs:
            try:
                if platform.system() == "Windows":
                    # On Windows, we run it all within a single Powershell script
                    if config == "icpp.toml":
                        if canister_path.name == "files":
                            run_shell_cmd(
                                SCRIPTS_PATH / "smoketest-files.ps1",
                                run_in_powershell=True,
                                cwd=canister_path,
                            )
                        else:
                            run_shell_cmd(
                                SCRIPTS_PATH / "smoketest.ps1",
                                run_in_powershell=True,
                                cwd=canister_path,
                            )
                else:
                    # On Mac & Ubuntu, it is much more flexible
                    typer.echo("--\nStop the local network")
                    run_dfx_cmd("stop")

                    typer.echo("--\nStart a clean local network")
                    run_dfx_cmd("start --clean --background")

                    typer.echo(f"--\nBuild the wasm with config {config}")
                    run_shell_cmd(
                        f"icpp build-wasm --config {config} --to-compile all",
                        cwd=canister_path,
                    )

                    typer.echo(f"--\nDeploy {canister_path.name}")
                    run_dfx_cmd("deploy", cwd=canister_path)

                    typer.echo(f"--\nRun pytest on {test_api_path}")
                    run_shell_cmd(
                        f"pytest --network=local {test_api_path}", cwd=ROOT_PATH
                    )

                    if canister_path.name == "files":
                        typer.echo(
                            "For the files canister, we verify that "
                            "files persist across a canister upgrade"
                        )

                        typer.echo(
                            f"--\nDeploy {canister_path.name} with forced upgrade"
                        )
                        run_dfx_cmd("deploy --upgrade-unchanged", cwd=canister_path)

                        typer.echo(
                            f"--\nRun pytest on {test_api_path} for tests "
                            "marked with 'run_after_upgrade'"
                        )
                        run_shell_cmd(
                            f"pytest --network=local -m run_after_upgrade "
                            f"{test_api_path}",
                            cwd=ROOT_PATH,
                        )

                    typer.echo("--\nStop the local network")
                    run_dfx_cmd("stop")

            except subprocess.CalledProcessError as e:
                typer.echo("--\nSomething did not pass")
                if platform.system() != "Windows":
                    run_dfx_cmd("stop")
                return e.returncode

    typer.echo("--\nCongratulations, everything passed!")
    try:
        typer.echo("💯 🎉 🏁")
    except UnicodeEncodeError:
        typer.echo(" ")
    return 0


if __name__ == "__main__":
    sys.exit(main())
