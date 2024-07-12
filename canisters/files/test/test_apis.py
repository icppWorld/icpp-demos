"""Test canister APIs

   First deploy the canister, then run:

   $ pytest --network=[local/ic] test_apis.py

"""

# pylint: disable=missing-function-docstring, unused-import, unused-argument, wildcard-import, unused-wildcard-import, line-too-long

from pathlib import Path
from typing import Dict
import pytest
from icpp.smoketest import call_canister_api, dict_to_candid_text

# Path to the dfx.json file
DFX_JSON_PATH = Path(__file__).parent / "../dfx.json"

# Canister in the dfx.json file we want to test
CANISTER_NAME = "files"


def test__health(identity_anonymous: dict[str, str], network: str) -> None:
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="health",
        canister_argument="()",
        network=network,
        timeout_seconds=10,
    )
    expected_response = "(variant { Ok = record { status_code = 200 : nat16;} })"
    assert response == expected_response


def test__write_read_during_query(network: str) -> None:
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="write_read_during_query",
        canister_argument="()",
        network=network,
    )
    expected_response = '(variant { Ok = record { data = vec { "Hello "; "from the "; "internal data file!";}; header = "_data_";} })'
    assert response == expected_response


# the file still does not exist after a query
# def test__file_download_chunk_1(network: str) -> None:
#     response = call_canister_api(
#         dfx_json_path=DFX_JSON_PATH,
#         canister_name=CANISTER_NAME,
#         canister_method="file_download_chunk",
#         canister_argument='(record { filename="internal_data_file"; chunksize=2000000 : nat64; offset=0 : nat64 })',
#         network=network,
#     )
#     expected_response = '(variant { Err = variant { Other = "file_download_chunk: ERROR: failed to open ifstream for file internal_data_file" } })'
#     assert response == expected_response


def test__write_read_during_update(network: str) -> None:
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="write_read_during_update",
        canister_argument="()",
        network=network,
    )
    expected_response = '(variant { Ok = record { data = vec { "Hello "; "from the "; "internal data file!";}; header = "_data_";} })'
    assert response == expected_response


# After an update, it is persisted, and we are able to download it
def test__file_download_chunk_2(network: str) -> None:
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="file_download_chunk",
        canister_argument='(record { filename="internal_data_file"; chunksize=2000000 : nat64; offset=0 : nat64 })',
        network=network,
    )
    expected_response = r'(variant { Ok = record { done = true; chunk = blob "\5f\64\61\74\61\5f\06\00\00\00\48\65\6c\6c\6f\20\09\00\00\00\66\72\6f\6d\20\74\68\65\20\13\00\00\00\69\6e\74\65\72\6e\61\6c\20\64\61\74\61\20\66\69\6c\65\21"; offset = 0 : nat64; filesize = 52 : nat64; chunksize = 52 : nat64;} })'
    assert response == expected_response


# and we are able to download it N bytes at a time
def test__file_download_chunk_0_to_9(network: str) -> None:
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="file_download_chunk",
        canister_argument='(record { filename="internal_data_file"; chunksize=10 : nat64; offset=0 : nat64 })',
        network=network,
    )
    expected_response = r'(variant { Ok = record { done = false; chunk = blob "\5f\64\61\74\61\5f\06\00\00\00"; offset = 0 : nat64; filesize = 52 : nat64; chunksize = 10 : nat64;} })'
    assert response == expected_response


def test__file_download_chunk_10_to_19(network: str) -> None:
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="file_download_chunk",
        canister_argument='(record { filename="internal_data_file"; chunksize=10 : nat64; offset=10 : nat64 })',
        network=network,
    )
    expected_response = r'(variant { Ok = record { done = false; chunk = blob "\48\65\6c\6c\6f\20\09\00\00\00"; offset = 10 : nat64; filesize = 52 : nat64; chunksize = 10 : nat64;} })'
    assert response == expected_response


# The last 10 bytes
def test__file_download_chunk_last_10(network: str) -> None:
    response = call_canister_api(
        dfx_json_path=DFX_JSON_PATH,
        canister_name=CANISTER_NAME,
        canister_method="file_download_chunk",
        canister_argument='(record { filename="internal_data_file"; chunksize=10 : nat64; offset=42 : nat64 })',
        network=network,
    )
    expected_response = r'(variant { Ok = record { done = true; chunk = blob "data file!"; offset = 42 : nat64; filesize = 52 : nat64; chunksize = 10 : nat64;} })'
    assert response == expected_response
