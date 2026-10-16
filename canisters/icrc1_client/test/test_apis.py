"""Test the ICRC-1 client against an ICRC-1 ledger

First deploy (icp deploy), then run:

$ pytest --network=local
"""

# pylint: disable=missing-function-docstring, unused-import, wildcard-import, unused-wildcard-import, redefined-outer-name

from pathlib import Path

from icpp.smoketest import call_canister_api, flatten_candid_text

from .conftest import INITIAL_BALANCE

ICP_YAML_PATH = Path(__file__).parent / "../icp.yaml"
FEE = 10_000


def call(network: str, method: str, argument: str) -> str:
    return flatten_candid_text(
        call_canister_api(
            icp_yaml_path=ICP_YAML_PATH,
            canister_name="icrc1_client",
            canister_method=method,
            canister_argument=argument,
            network=network,
            timeout_seconds=120,
        )
    )


def balance(network: str, ledger: str) -> int:
    response = call(network, "balance", f'(principal "{ledger}")')
    return int(response.strip("()").split(":")[0].strip().replace("_", ""))


def test__token_info(network: str, ledger: str) -> None:
    # Three queries of the ledger, at the same time
    response = call(network, "token_info", f'(principal "{ledger}")')
    assert response == '("TEST: fee 10000, 8 decimals")'


def test__transfer(network: str, ledger: str) -> None:
    before = balance(network, ledger)
    assert before <= INITIAL_BALANCE
    response = call(
        network,
        "transfer",
        f'(principal "{ledger}", principal "aaaaa-aa", 1_000_000 : nat)',
    )
    assert response.startswith('("Ok: block '), response
    assert balance(network, ledger) == before - 1_000_000 - FEE


def test__transfer_insufficient_funds(network: str, ledger: str) -> None:
    before = balance(network, ledger)
    response = call(
        network,
        "transfer",
        f'(principal "{ledger}", principal "aaaaa-aa", {INITIAL_BALANCE * 10} : nat)',
    )
    assert response == f'("Err: InsufficientFunds, balance {before}")'
    assert balance(network, ledger) == before
