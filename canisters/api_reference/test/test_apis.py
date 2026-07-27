"""Test canister APIs

First deploy the canister, then run:

$ pytest --network=[local/ic] test_apis.py

"""

# pylint: disable=missing-function-docstring, unused-import, wildcard-import, unused-wildcard-import, line-too-long, unused-argument

from pathlib import Path
import pytest
from icpp.smoketest import call_canister_api, flatten_candid_text

# Path to the icp.yaml file
ICP_YAML_PATH = Path(__file__).parent / "../icp.yaml"

# Canister in the icp.yaml file we want to test
CANISTER_NAME = "demo"

# -------------------------------------------------------------------------------
# IC_API - ic0 system interface


def test__demo_candid_type_bool(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_bool",
        canister_argument="(true)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(true)"
    assert response == expected_response


def test__demo_candid_type_bools(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_bools",
        canister_argument="(true, false)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(true, false)"
    assert response == expected_response


def test__demo_candid_type_float32(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_float32",
        canister_argument="(0.1 : float32)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(0.1 : float32)"
    assert response == expected_response


def test__demo_candid_type_float32s(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_float32s",
        canister_argument="(0.1 : float32, -1.2 : float32)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(0.1 : float32, -1.2 : float32)"
    assert response == expected_response


def test__demo_candid_type_float64(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_float64",
        canister_argument="(0.1 : float64)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(0.1 : float64)"
    assert response == expected_response


def test__demo_candid_type_float64s(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_float64s",
        canister_argument="(0.1 : float64, -1.2 : float64)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(0.1 : float64, -1.2 : float64)"
    assert response == expected_response


def test__demo_candid_type_int8(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_int8",
        canister_argument="(101 : int8)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : int8)"
    assert response == expected_response


def test__demo_candid_type_int8s(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_int8s",
        canister_argument="(101 : int8, -102 : int8)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : int8, -102 : int8)"
    assert response == expected_response


def test__demo_candid_type_int16(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_int16",
        canister_argument="(101 : int16)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : int16)"
    assert response == expected_response


def test__demo_candid_type_int16s(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_int16s",
        canister_argument="(101 : int16, -102 : int16)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : int16, -102 : int16)"
    assert response == expected_response


def test__demo_candid_type_int32(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_int32",
        canister_argument="(101 : int32)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : int32)"
    assert response == expected_response


def test__demo_candid_type_int32s(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_int32s",
        canister_argument="(101 : int32, -102 : int32)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : int32, -102 : int32)"
    assert response == expected_response


def test__demo_candid_type_int64(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_int64",
        canister_argument="(101 : int64)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : int64)"
    assert response == expected_response


def test__demo_candid_type_int64s(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_int64s",
        canister_argument="(101 : int64, -102 : int64)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : int64, -102 : int64)"
    assert response == expected_response


def test__demo_candid_type_int(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_int",
        canister_argument="(101 : int)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : int)"
    assert response == expected_response


def test__demo_candid_type_ints(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_ints",
        canister_argument="(101 : int, -102 : int)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : int, -102 : int)"
    assert response == expected_response


def test__demo_candid_type_nat8(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_nat8",
        canister_argument="(101 : nat8)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : nat8)"
    assert response == expected_response


def test__demo_candid_type_nat8s(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_nat8s",
        canister_argument="(101 : nat8, 102 : nat8)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : nat8, 102 : nat8)"
    assert response == expected_response


def test__demo_candid_type_nat16(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_nat16",
        canister_argument="(101 : nat16)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : nat16)"
    assert response == expected_response


def test__demo_candid_type_nat16s(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_nat16s",
        canister_argument="(101 : nat16, 102 : nat16)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : nat16, 102 : nat16)"
    assert response == expected_response


def test__demo_candid_type_nat32(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_nat32",
        canister_argument="(101 : nat32)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : nat32)"
    assert response == expected_response


def test__demo_candid_type_nat32s(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_nat32s",
        canister_argument="(101 : nat32, 102 : nat32)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : nat32, 102 : nat32)"
    assert response == expected_response


def test__demo_candid_type_nat64(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_nat64",
        canister_argument="(101 : nat64)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : nat64)"
    assert response == expected_response


def test__demo_candid_type_nat64s(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_nat64s",
        canister_argument="(101 : nat64, 102 : nat64)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : nat64, 102 : nat64)"
    assert response == expected_response


def test__demo_candid_type_nat(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_nat",
        canister_argument="(101 : nat)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : nat)"
    assert response == expected_response


def test__demo_candid_type_nats(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_nats",
        canister_argument="(101 : nat, 102 : nat)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(101 : nat, 102 : nat)"
    assert response == expected_response


def test__demo_candid_type_opt(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_opt",
        canister_argument="(opt (true : bool))",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "(opt true)"
    assert response == expected_response


def test__demo_candid_type_opts(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_opts",
        canister_argument="4449444c0f6e7e6e736e726e776e766e756e746e7c6e7b6e7a6e796e786e7d6e686e710f000102030405060708090a0b0c0d0e010101cdcccc3d019a9999999999c93f01f801f0ff01e0ffffff01c0ffffffffffffff01807f0108011000012000000001400000000000000001800101010100010464656d6f",
        canister_input="raw",
        canister_output="raw",
        network=network,
    )
    expected_response = "4449444c0f6e7e6e736e726e776e766e756e746e7c6e7b6e7a6e796e786e7d6e686e710f000102030405060708090a0b0c0d0e010101cdcccc3d019a9999999999c93f01f801f0ff01e0ffffff01c0ffffffffffffff01807f0108011000012000000001400000000000000001800101010100010464656d6f"
    assert response == expected_response


def test__demo_candid_type_principal(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_principal",
        canister_argument='(principal "2ibo7-dia")',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = '(principal "2ibo7-dia")'
    assert response == expected_response


def test__demo_candid_type_principals(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_principals",
        canister_argument='(principal "2ibo7-dia", principal "w3gef-eqbai")',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = '(principal "2ibo7-dia", principal "w3gef-eqbai")'
    assert response == expected_response


def test__demo_candid_type_record(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_record",
        canister_argument='(record {"field 1" = true : bool; "field 2" = 0.1 : float32; "field 3" = 0.2 : float64; "field 4" = -8 : int8; "field 5" = -16 : int16; "field 6" = -32 : int32; "field 7" = -64 : int64; "field 8" = -128 : int; "field 9" = 8 : nat8; "field 10" = 16 : nat16; "field A" = 32 : nat32; "field B" = 64 : nat64; "field C" = 128 : nat; "field D" = principal "2ibo7-dia"; "field E" = "demo" : text;})',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    # icp-cli pretty-prints a record over several lines -> compare flattened
    expected_response = '( record { "field 10" = 16 : nat16; "field 1" = true; "field 2" = 0.1 : float32; "field 3" = 0.2 : float64; "field 4" = -8 : int8; "field 5" = -16 : int16; "field 6" = -32 : int32; "field 7" = -64 : int64; "field 8" = -128 : int; "field 9" = 8 : nat8; "field A" = 32 : nat32; "field B" = 64 : nat64; "field C" = 128 : nat; "field D" = principal "2ibo7-dia"; "field E" = "demo"; }, )'
    assert flatten_candid_text(response) == expected_response


def test__demo_candid_type_records(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_records",
        canister_argument='(record {"field 1A" = -8 : int8;}, record {"field 2A" = -16 : int16;})',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = (
        '(record { "field 1A" = -8 : int8 }, record { "field 2A" = -16 : int16 })'
    )
    assert response == expected_response


def test__demo_candid_type_text(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_text",
        canister_argument='("demo A" : text)',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = '("demo A")'
    assert response == expected_response


def test__demo_candid_type_texts(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_texts",
        canister_argument='("demo A" : text, "demo B" : text)',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = '("demo A", "demo B")'
    assert response == expected_response


def test__demo_candid_type_variant(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_variant",
        canister_argument='(variant { "field 2" = 0.1 : float32 })',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response_1 = "(variant { field 2 = 0.1 : float32 })"
    expected_response_2 = '(variant { "field 2" = 0.1 : float32 })'
    assert response in (expected_response_1, expected_response_2)


def test__demo_candid_type_variants(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_candid_type_variants",
        canister_argument='(variant { "field 2" = 0.1 : float32 }, variant { "field 2" = 0.1 : float32 })',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response_1 = (
        "(variant { field 2 = 0.1 : float32 }, variant { field 2 = 0.1 : float32 })"
    )
    expected_response_2 = (
        '(variant { "field 2" = 0.1 : float32 }, variant { "field 2" = 0.1 : float32 })'
    )
    assert response in (expected_response_1, expected_response_2)


# -------------------------------------------------------------------------------
# IC_API - ic0 system interface


def test__demo_debug_print(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_debug_print",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "()"
    assert response == expected_response


def test__demo_ic_api(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_ic_api",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "()"
    assert response == expected_response


def test__demo_get_caller(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_get_caller",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = f'( "Hello! Your principal is {principal}", )'
    assert flatten_candid_text(response) == expected_response


def test__demo_from_wire_no_arg(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_from_wire_no_arg",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "()"
    assert response == expected_response


def test__demo_from_wire_one_arg(network: str, principal: str) -> None:
    hobby = "Neuron Staking"
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_from_wire_one_arg",
        canister_argument=f'("{hobby}")',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = f'( "Hello {principal}, your hobby is {hobby}", )'
    assert flatten_candid_text(response) == expected_response


def test__demo_from_wire_multiple_args(network: str, principal: str) -> None:
    hobby = "Neuron Staking"
    num_icp = 3000

    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_from_wire_multiple_args",
        canister_argument=f'("{hobby}", {num_icp} : nat64)',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = (
        f'( "Hello {principal}, you earned {num_icp} ICP from your hobby, {hobby}", )'
    )
    assert flatten_candid_text(response) == expected_response


def test__demo_time(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_time",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response_starts_with = '( "The current system time in nanoseconds:'
    assert flatten_candid_text(response).startswith(expected_response_starts_with)


# -------------------------------------------------------------------------------
# Timers — IC_API::set_timer / set_timer_recurring / cancel_timer / cancel_all_timers
#
# The IC fires `canister_global_timer` automatically; tests poll the counter
# query methods up to a deadline rather than sleeping a fixed duration.


def _poll_one_shot_fires(network: str, deadline_s: float = 10.0) -> int:
    import time

    end = time.monotonic() + deadline_s
    last = 0
    while time.monotonic() < end:
        response = call_canister_api(
            icp_yaml_path=ICP_YAML_PATH,
            canister_name=CANISTER_NAME,
            canister_method="demo_get_one_shot_fires",
            canister_argument="()",
            canister_input="idl",
            canister_output="idl",
            network=network,
        )
        # response is e.g. '(1 : nat64)'
        last = int(response.strip("()").split(":")[0].strip().replace("_", ""))
        if last >= 1:
            return last
        time.sleep(0.25)
    return last


def _poll_recurring_fires(network: str, target: int, deadline_s: float = 10.0) -> int:
    import time

    end = time.monotonic() + deadline_s
    last = 0
    while time.monotonic() < end:
        response = call_canister_api(
            icp_yaml_path=ICP_YAML_PATH,
            canister_name=CANISTER_NAME,
            canister_method="demo_get_recurring_fires",
            canister_argument="()",
            canister_input="idl",
            canister_output="idl",
            network=network,
        )
        last = int(response.strip("()").split(":")[0].strip().replace("_", ""))
        if last >= target:
            return last
        time.sleep(0.25)
    return last


def _parse_nat64(response: str) -> int:
    # response is e.g. '(1 : nat64)'
    return int(response.strip("()").split(":")[0].strip().replace("_", ""))


def test__demo_reset_timer_counters(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_reset_timer_counters",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    assert response == "()"

    # Both counters should now be 0.
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_get_one_shot_fires",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    assert _parse_nat64(response) == 0

    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_get_recurring_fires",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    assert _parse_nat64(response) == 0


def test__demo_set_timer(network: str, principal: str) -> None:
    # Clean slate.
    call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_reset_timer_counters",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )

    # Schedule a one-shot at delay 0 — IC fires it on the next round.
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_set_timer",
        canister_argument="(0 : nat64)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    timer_id = _parse_nat64(response)
    assert timer_id > 0

    # Poll until the callback fires.
    fires = _poll_one_shot_fires(network)
    assert fires >= 1, f"expected one-shot to fire at least once, got {fires}"


def test__demo_set_timer_recurring(network: str, principal: str) -> None:
    # Clean slate.
    call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_reset_timer_counters",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )

    # 200 ms period — fires fast enough to observe several within deadline.
    period_ns = 200_000_000
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_set_timer_recurring",
        canister_argument=f"({period_ns} : nat64)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    timer_id = _parse_nat64(response)
    assert timer_id > 0

    # Wait for at least 2 firings, then cancel by id.
    fires = _poll_recurring_fires(network, target=2)
    assert fires >= 2, f"expected recurring to fire >=2 times, got {fires}"

    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_cancel_timer",
        canister_argument=f"({timer_id} : nat64)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    assert response == "(true)"


def test__demo_cancel_timer(network: str, principal: str) -> None:
    # Cancelling an unknown id returns false (no exceptions).
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_cancel_timer",
        canister_argument="(999_999 : nat64)",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    assert response == "(false)"


def test__demo_cancel_all_timers(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_cancel_all_timers",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    assert response == "()"


def test__demo_get_one_shot_fires(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_get_one_shot_fires",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    # Counter is monotonic across the suite — just assert it's well-formed.
    assert _parse_nat64(response) >= 0


def test__demo_get_recurring_fires(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_get_recurring_fires",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    assert _parse_nat64(response) >= 0


def test__demo_to_wire_no_arg(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_to_wire_no_arg",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "()"
    assert response == expected_response


def test__demo_to_wire_one_arg(network: str, principal: str) -> None:
    hobby = "Neuron Staking"
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_to_wire_one_arg",
        canister_argument=f'("{hobby}")',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = f'( "Hello {principal}, your hobby is {hobby}", )'
    assert flatten_candid_text(response) == expected_response


def test__demo_to_wire_multiple_args(network: str, principal: str) -> None:
    hobby = "Neuron Staking"
    num_icp = 3000

    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_to_wire_multiple_args",
        canister_argument=f'("{hobby}", {num_icp} : nat64)',
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = f'( "{principal}", "{hobby}", {num_icp:_} : nat64, "ICP", )'
    assert flatten_candid_text(response) == expected_response


# -------------------------------------------------------------------------------
# IC_API - utilities


def test__demo_string_to_int128(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_string_to_int128",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "()"
    assert response == expected_response


def test__demo_to_string_128(network: str, principal: str) -> None:
    response = call_canister_api(
        icp_yaml_path=ICP_YAML_PATH,
        canister_name=CANISTER_NAME,
        canister_method="demo_to_string_128",
        canister_argument="()",
        canister_input="idl",
        canister_output="idl",
        network=network,
    )
    expected_response = "()"
    assert response == expected_response
