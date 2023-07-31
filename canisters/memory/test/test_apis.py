"""Test canister APIs

   First deploy the canister, then run:

   $ pytest --network=[local/ic]

"""
# pylint: disable=missing-function-docstring, unused-import, wildcard-import, unused-wildcard-import, line-too-long

from pathlib import Path
import pytest
from icpp.smoketest import call_canister_api

# Path to the dfx.json file
DFX_JSON_PATH = Path(__file__).parent / "../dfx.json"

# Canister in the dfx.json file we want to test
CANISTER_NAME = "memory"


def test__memory(network: str) -> None:
    # for IC network, the update calls take longer
    update_timeout_seconds = 3
    if network == "ic":
        update_timeout_seconds = 10
    # ------------------------------------------------
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="change_memory",
        canister_argument="()",
        network=network,
        timeout_seconds=update_timeout_seconds,
    )
    expected_response = ""
    assert response == expected_response

    # ------------------------------------------------
    # print it (only does something in local network)
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="print_memory",
        canister_argument="()",
        network=network,
    )
    expected_response = ""
    assert response == expected_response
