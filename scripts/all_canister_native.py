"""Runs the native tests for all canisters"""

import sys
from pathlib import Path
import subprocess
import typer
from icpp.run_shell_cmd import run_shell_cmd


ROOT_PATH = Path(__file__).parent.parent


def main() -> int:
    """build-native and run mockic.exe"""
    canister_paths = list((ROOT_PATH / "canisters").glob("*"))
    for canister_path in canister_paths:
        try:
            typer.echo("--\nicpp build-native")
            run_shell_cmd("icpp build-native", cwd=canister_path)

            typer.echo("--\nRun mockic.exe")
            run_shell_cmd("./build-native/mockic.exe", cwd=canister_path)

        except subprocess.CalledProcessError as e:
            typer.echo("--\nSomething did not pass")
            return e.returncode

    typer.echo("--\nCongratulations, everything passed!")
    typer.echo("💯 🎉 🏁")
    return 0


if __name__ == "__main__":
    sys.exit(main())
