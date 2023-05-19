"""Deploys & tests all canisters in a freshly started local network"""

import sys
from pathlib import Path
import subprocess
import typer
from icpp.run_shell_cmd import run_shell_cmd


ROOT_PATH = Path(__file__).parent.parent


def main() -> int:
    """Start local network; Deploy canister; Pytest"""
    canister_paths = list((ROOT_PATH / "canisters").glob("*"))
    for canister_path in canister_paths:
        test_api_path = canister_path / "test/test_apis.py"
        try:
            typer.echo("--\nStop the local network")
            run_shell_cmd("dfx stop")

            typer.echo("--\nStart a clean local network")
            run_shell_cmd("dfx start --clean --background")

            typer.echo(f"--\nDeploy {canister_path.name}")
            run_shell_cmd("dfx deploy", cwd=canister_path)

            typer.echo(f"--\nRun pytest on {test_api_path}")
            run_shell_cmd(f"pytest --network=local {test_api_path}", cwd=ROOT_PATH)

            typer.echo("--\nStop the local network")
            run_shell_cmd("dfx stop")

        except subprocess.CalledProcessError as e:
            typer.echo("--\nSomething did not pass\nStop the local network")
            run_shell_cmd("dfx stop")
            return e.returncode

    typer.echo("--\nCongratulations, everything passed!")
    typer.echo("💯 🎉 🏁")
    return 0


if __name__ == "__main__":
    sys.exit(main())
