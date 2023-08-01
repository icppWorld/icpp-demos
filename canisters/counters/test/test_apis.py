"""Test canister APIs

   First deploy the canister, then run:

   $ pytest --network=[local/ic]

"""
# pylint: disable=missing-function-docstring, unused-import, wildcard-import, unused-wildcard-import, line-too-long, unused-argument

from pathlib import Path
import pytest
from icpp.smoketest import call_canister_api

# Path to the dfx.json file
DFX_JSON_PATH = Path(__file__).parent / "../dfx.json"

# Canister in the dfx.json file we want to test
CANISTER_NAME = "counters"


def test__counters(identity_default: dict[str, str], network: str) -> None:
    # for IC network, the update calls take longer
    update_timeout_seconds = 3
    if network == "ic":
        update_timeout_seconds = 10
    # ------------------------------------------------
    # Set the counter to 10
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="write_counters",
        canister_argument="(vec { 10 : nat64; 10 : nat64 })",
        network=network,
        timeout_seconds=update_timeout_seconds,
    )
    expected_response = ""
    assert response == expected_response

    # ------------------------------------------------
    # Increment the counter
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="inc_counters",
        canister_argument="()",
        network=network,
        timeout_seconds=update_timeout_seconds,
    )
    expected_response = ""
    assert response == expected_response

    # ------------------------------------------------
    # Read the counter and check value is 11
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="read_counters",
        canister_argument="()",
        network=network,
    )
    expected_response = "(vec { 11 : nat64; 11 : nat64;})"
    assert response == expected_response
