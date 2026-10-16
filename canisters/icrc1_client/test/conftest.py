"""The pytest fixtures
https://docs.pytest.org/en/latest/fixture.html
"""

# pylint: disable=missing-function-docstring, unused-import, wildcard-import, unused-wildcard-import, line-too-long, unused-argument, redefined-outer-name
import subprocess
from pathlib import Path

import pytest
from icpp.conftest_base import *  # pytest fixtures provided by icpp
from icpp.smoketest import ICP, get_canister_id

ICP_YAML_PATH = Path(__file__).parent / "../icp.yaml"

# The balance the ledger gives icrc1_client
INITIAL_BALANCE = 1_000_000_000


@pytest.fixture(scope="session")
def ledger(network: str, identity: str, principal: str) -> str:
    """Reinstalls the ledger with a balance for icrc1_client, and returns its
    principal. The principals of a deployment are only known once the
    canisters exist, so icp.yaml installs the ledger without balances. The
    minting account is the test identity."""
    client = get_canister_id(
        canister_name="icrc1_client", icp_yaml_path=ICP_YAML_PATH, network=network
    )
    ledger_id = get_canister_id(
        canister_name="icrc1_ledger", icp_yaml_path=ICP_YAML_PATH, network=network
    )
    args = (
        "(variant { Init = record {"
        ' token_symbol = "TEST"; token_name = "Test Token";'
        f' minting_account = record {{ owner = principal "{principal}" }};'
        " transfer_fee = 10_000 : nat; metadata = vec {};"
        f' initial_balances = vec {{ record {{ record {{ owner = principal "{client}" }};'
        f" {INITIAL_BALANCE} : nat }} }};"
        " archive_options = record { num_blocks_to_archive = 1000 : nat64;"
        f' trigger_threshold = 2000 : nat64; controller_id = principal "{principal}" }};'
        " } })"
    )
    subprocess.run(
        [
            ICP,
            "canister",
            "install",
            "icrc1_ledger",
            "--mode",
            "reinstall",
            "--args",
            args,
            "--environment",
            network,
            "--identity",
            identity,
            "--yes",
        ],
        cwd=ICP_YAML_PATH.parent,
        check=True,
        capture_output=True,
        text=True,
        stdin=subprocess.DEVNULL,
    )
    return ledger_id
