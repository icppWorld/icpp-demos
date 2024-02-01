// C++ canister containing all api-reference examples of the docs

// Main entry point for a native debug executable.
// Build it with: `icpp build-native` from the parent folder where 'icpp.toml' resides

#include "main.h"

#include <iostream>

// clang-format off
#include "../src/demo_candid_type_bool.h"
#include "../src/demo_candid_type_float32.h"
#include "../src/demo_candid_type_float64.h"
#include "../src/demo_candid_type_int8.h"
#include "../src/demo_candid_type_int16.h"
#include "../src/demo_candid_type_int32.h"
#include "../src/demo_candid_type_int64.h"
#include "../src/demo_candid_type_int.h"
#include "../src/demo_candid_type_nat8.h"
#include "../src/demo_candid_type_nat16.h"
#include "../src/demo_candid_type_nat32.h"
#include "../src/demo_candid_type_nat64.h"
#include "../src/demo_candid_type_nat.h"
#include "../src/demo_candid_type_opt.h"
#include "../src/demo_candid_type_principal.h"
#include "../src/demo_candid_type_record.h"
#include "../src/demo_candid_type_text.h"
#include "../src/demo_candid_type_variant.h"

#include "../src/demo_debug_print.h"
#include "../src/demo_from_wire.h"
#include "../src/demo_get_caller.h"
#include "../src/demo_ic_api.h"
#include "../src/demo_string_to_int128.h"
#include "../src/demo_time.h"
#include "../src/demo_trap.h"

#include "../src/demo_to_string_128.h"
#include "../src/demo_to_wire.h"

// clang-format on

// The Mock IC
#include "mock_ic.h"

int main() {
  MockIC mockIC(true); // 'true' will debug_print

  // -----------------------------------------------------------------------------
  // Configs for the tests:

  // The pretend principal of the caller
  std::string my_principal{
      "expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae"};

  bool silent_on_trap = true;

  // -----------------------------------------------------------------------------
  // CandidTypes

  // '(true)' -> same
  mockIC.run_test("demo_candid_type_bool", demo_candid_type_bool,
                  "4449444c00017e01", // didc encode '(true)'
                  "4449444c00017e01", // didc decode 4449444c00017e01
                  silent_on_trap, my_principal);

  // '(true, false)' -> same
  mockIC.run_test("demo_candid_type_bools", demo_candid_type_bools,
                  "4449444c00027e7e0100", "4449444c00027e7e0100",
                  silent_on_trap, my_principal);

  // '(0.1 : float32)' -> same
  mockIC.run_test("demo_candid_type_float32", demo_candid_type_float32,
                  "4449444c000173cdcccc3d", "4449444c000173cdcccc3d",
                  silent_on_trap, my_principal);

  // '(0.1 : float32, -1.2 : float32)' -> same
  mockIC.run_test("demo_candid_type_float32s", demo_candid_type_float32s,
                  "4449444c00027373cdcccc3d9a9999bf",
                  "4449444c00027373cdcccc3d9a9999bf", silent_on_trap,
                  my_principal);

  // '(0.1 : float64)' -> same
  mockIC.run_test("demo_candid_type_float64", demo_candid_type_float64,
                  "4449444c0001729a9999999999b93f",
                  "4449444c0001729a9999999999b93f", silent_on_trap,
                  my_principal);

  // '(0.1 : float64, -1.2 : float64)' -> same
  mockIC.run_test("demo_candid_type_float64s", demo_candid_type_float64s,
                  "4449444c000272729a9999999999b93f333333333333f3bf",
                  "4449444c000272729a9999999999b93f333333333333f3bf",
                  silent_on_trap, my_principal);

  // '(101 : int8)' -> same
  mockIC.run_test("demo_candid_type_int8", demo_candid_type_int8,
                  "4449444c00017765", "4449444c00017765", silent_on_trap,
                  my_principal);

  // '(101 : int8, -102 : int8)' -> same
  mockIC.run_test("demo_candid_type_int8s", demo_candid_type_int8s,
                  "4449444c00027777659a", "4449444c00027777659a",
                  silent_on_trap, my_principal);

  // '(101 : int16)' -> same
  mockIC.run_test("demo_candid_type_int16", demo_candid_type_int16,
                  "4449444c0001766500", "4449444c0001766500", silent_on_trap,
                  my_principal);

  // '(101 : int16, -102 : int16)' -> same
  mockIC.run_test("demo_candid_type_int16s", demo_candid_type_int16s,
                  "4449444c0002767665009aff", "4449444c0002767665009aff",
                  silent_on_trap, my_principal);

  // '(101 : int32)' -> same
  mockIC.run_test("demo_candid_type_int32", demo_candid_type_int32,
                  "4449444c00017565000000", "4449444c00017565000000",
                  silent_on_trap, my_principal);

  // '(101 : int32, -102 : int32)' -> same
  mockIC.run_test("demo_candid_type_int32s", demo_candid_type_int32s,
                  "4449444c00027575650000009affffff",
                  "4449444c00027575650000009affffff", silent_on_trap,
                  my_principal);

  // '(101 : int64)' -> same
  mockIC.run_test("demo_candid_type_int64", demo_candid_type_int64,
                  "4449444c0001746500000000000000",
                  "4449444c0001746500000000000000", silent_on_trap,
                  my_principal);

  // '(101 : int64, -102 : int64)' -> same
  mockIC.run_test("demo_candid_type_int64s", demo_candid_type_int64s,
                  "4449444c0002747465000000000000009affffffffffffff",
                  "4449444c0002747465000000000000009affffffffffffff",
                  silent_on_trap, my_principal);

  // '(101 : int)' -> same
  mockIC.run_test("demo_candid_type_int", demo_candid_type_int,
                  "4449444c00017ce500", "4449444c00017ce500", silent_on_trap,
                  my_principal);

  // '(101 : int, -102 : int)' -> same
  mockIC.run_test("demo_candid_type_ints", demo_candid_type_ints,
                  "4449444c00027c7ce5009a7f", "4449444c00027c7ce5009a7f",
                  silent_on_trap, my_principal);

  // '(101 : nat8)' -> same
  mockIC.run_test("demo_candid_type_nat8", demo_candid_type_nat8,
                  "4449444c00017b65", "4449444c00017b65", silent_on_trap,
                  my_principal);

  // '(101 : nat8, 102 : nat8)' -> same
  mockIC.run_test("demo_candid_type_nat8s", demo_candid_type_nat8s,
                  "4449444c00027b7b6566", "4449444c00027b7b6566",
                  silent_on_trap, my_principal);

  // '(101 : nat16)' -> same
  mockIC.run_test("demo_candid_type_nat16", demo_candid_type_nat16,
                  "4449444c00017a6500", "4449444c00017a6500", silent_on_trap,
                  my_principal);

  // '(101 : nat16, 102 : nat16)' -> same
  mockIC.run_test("demo_candid_type_nat16s", demo_candid_type_nat16s,
                  "4449444c00027a7a65006600", "4449444c00027a7a65006600",
                  silent_on_trap, my_principal);

  // '(101 : nat32)' -> same
  mockIC.run_test("demo_candid_type_nat32", demo_candid_type_nat32,
                  "4449444c00017965000000", "4449444c00017965000000",
                  silent_on_trap, my_principal);

  // '(101 : nat32, 102 : nat32)' -> same
  mockIC.run_test("demo_candid_type_nat32s", demo_candid_type_nat32s,
                  "4449444c000279796500000066000000",
                  "4449444c000279796500000066000000", silent_on_trap,
                  my_principal);

  // '(101 : nat64)' -> same
  mockIC.run_test("demo_candid_type_nat64", demo_candid_type_nat64,
                  "4449444c0001786500000000000000",
                  "4449444c0001786500000000000000", silent_on_trap,
                  my_principal);

  // '(101 : nat64, 102 : nat64)' -> same
  mockIC.run_test("demo_candid_type_nat64s", demo_candid_type_nat64s,
                  "4449444c0002787865000000000000006600000000000000",
                  "4449444c0002787865000000000000006600000000000000",
                  silent_on_trap, my_principal);

  // '(101 : nat)' -> same
  mockIC.run_test("demo_candid_type_nat", demo_candid_type_nat,
                  "4449444c00017d65", "4449444c00017d65", silent_on_trap,
                  my_principal);

  // '(101 : nat, 102 : nat)' -> same
  mockIC.run_test("demo_candid_type_nats", demo_candid_type_nats,
                  "4449444c00027d7d6566", "4449444c00027d7d6566",
                  silent_on_trap, my_principal);

  // '(opt (true : bool))' -> same
  mockIC.run_test("demo_candid_type_opt", demo_candid_type_opt,
                  "4449444c016e7e01000101", "4449444c016e7e01000101",
                  silent_on_trap, my_principal);

  // '(opt (true : bool), opt (0.1 : float32), opt (0.2 : float64), opt (-8 : int8), opt (-16 : int16), opt (-32 : int32), opt (-64 : int64), opt (-128 : int), opt (8 : nat8), opt (16 : nat16), opt (32 : nat32), opt (64 : nat64), opt (128 : nat), opt (principal "2ibo7-dia"), opt ("demo" : text))'
  // -> same
  mockIC.run_test(
      "demo_candid_type_opts", demo_candid_type_opts,
      "4449444c0f6e7e6e736e726e776e766e756e746e7c6e7b6e7a6e796e786e7d6e686e710f000102030405060708090a0b0c0d0e010101cdcccc3d019a9999999999c93f01f801f0ff01e0ffffff01c0ffffffffffffff01807f0108011000012000000001400000000000000001800101010100010464656d6f",
      "4449444c0f6e7e6e736e726e776e766e756e746e7c6e7b6e7a6e796e786e7d6e686e710f000102030405060708090a0b0c0d0e010101cdcccc3d019a9999999999c93f01f801f0ff01e0ffffff01c0ffffffffffffff01807f0108011000012000000001400000000000000001800101010100010464656d6f",
      silent_on_trap, my_principal);

  // '(principal "2ibo7-dia")' -> same
  mockIC.run_test("demo_candid_type_principal", demo_candid_type_principal,
                  "4449444c000168010100", "4449444c000168010100",
                  silent_on_trap, my_principal);

  // '(principal "2ibo7-dia", principal "w3gef-eqbai")' -> same
  mockIC.run_test("demo_candid_type_principals", demo_candid_type_principals,
                  "4449444c0002686801010001020102",
                  "4449444c0002686801010001020102", silent_on_trap,
                  my_principal);

  // '(record {"field 1" = true : bool; "field 2" = 0.1 : float32; "field 3" = 0.2 : float64; "field 4" = -8 : int8; "field 5" = -16 : int16; "field 6" = -32 : int32; "field 7" = -64 : int64; "field 8" = -128 : int; "field 9" = 8 : nat8; "field 10" = 16 : nat16; "field A" = 32 : nat32; "field B" = 64 : nat64; "field C" = 128 : nat; "field D" = principal "2ibo7-dia"; "field E" = "demo" : text;})'
  // -> same
  mockIC.run_test(
      "demo_candid_type_record", demo_candid_type_record,
      "4449444c016c0f859dacdf0a7acba6b7e10f7ecca6b7e10f73cda6b7e10f72cea6b7e10f77cfa6b7e10f76d0a6b7e10f75d1a6b7e10f74d2a6b7e10f7cd3a6b7e10f7bdba6b7e10f79dca6b7e10f78dda6b7e10f7ddea6b7e10f68dfa6b7e10f710100100001cdcccc3d9a9999999999c93ff8f0ffe0ffffffc0ffffffffffffff807f0820000000400000000000000080010101000464656d6f",
      "4449444c016c0f859dacdf0a7acba6b7e10f7ecca6b7e10f73cda6b7e10f72cea6b7e10f77cfa6b7e10f76d0a6b7e10f75d1a6b7e10f74d2a6b7e10f7cd3a6b7e10f7bdba6b7e10f79dca6b7e10f78dda6b7e10f7ddea6b7e10f68dfa6b7e10f710100100001cdcccc3d9a9999999999c93ff8f0ffe0ffffffc0ffffffffffffff807f0820000000400000000000000080010101000464656d6f",
      silent_on_trap, my_principal);

  // '(record {"field 1A" = -8 : int8;}, record {"field 2A" = -16 : int16;})'
  // -> same
  mockIC.run_test("demo_candid_type_records", demo_candid_type_records,
                  "4449444c026c01969dacdf0a776c01f59eacdf0a76020001f8f0ff",
                  "4449444c026c01969dacdf0a776c01f59eacdf0a76020001f8f0ff",
                  silent_on_trap, my_principal);

  // '("demo A" : text)' -> '("demo A" : text)'
  mockIC.run_test("demo_candid_type_text", demo_candid_type_text,
                  "4449444c0001710664656d6f2041",
                  "4449444c0001710664656d6f2041", silent_on_trap, my_principal);

  // '("demo A" : text, "demo B" : text)' -> same
  mockIC.run_test("demo_candid_type_texts", demo_candid_type_texts,
                  "4449444c000271710664656d6f20410664656d6f2042",
                  "4449444c000271710664656d6f20410664656d6f2042",
                  silent_on_trap, my_principal);

  // '(variant {"field 2" = 0.1 : float32})'
  // -> same
  mockIC.run_test("demo_candid_type_variant", demo_candid_type_variant,
                  "4449444c016b01cca6b7e10f73010000cdcccc3d",
                  "4449444c016b01cca6b7e10f73010000cdcccc3d", silent_on_trap,
                  my_principal);

  // '(variant {"field 2" = 0.1 : float32}, variant {"field 2" = 0.1 : float32})'
  // -> same
  mockIC.run_test(
      "demo_candid_type_variants", demo_candid_type_variants,
      "4449444c016b01cca6b7e10f7302000000cdcccc3d00cdcccc3d",
      "4449444c026b01cca6b7e10f736b01cca6b7e10f7302000100cdcccc3d00cdcccc3d",
      silent_on_trap, my_principal);
  // -----------------------------------------------------------------------------
  // IC_API - ic0 system interface

  // '()' -> '()'
  mockIC.run_test("demo_debug_print", demo_debug_print, "4449444c0000",
                  "4449444c0000", silent_on_trap, my_principal);

  // '()' -> '()'
  mockIC.run_test("demo_ic_api", demo_ic_api, "4449444c0000", "4449444c0000",
                  silent_on_trap, my_principal);

  // '()' -> '("Hello! Your principal is expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae")'
  mockIC.run_test(
      "demo_get_caller", demo_get_caller, "4449444c0000",
      "4449444c0001715848656c6c6f2120596f7572207072696e636970616c206973206578706d742d67747873772d696e66746a2d747461626a2d71687035732d6e6f7a75702d6e3362626f2d6b377a766e2d64673468652d6b6e6163332d6c6165",
      silent_on_trap, my_principal);

  // '()' -> '()'
  mockIC.run_test("demo_from_wire_no_arg", demo_from_wire_no_arg,
                  "4449444c0000", "4449444c0000");

  // '("Neuron Staking")' ->
  // '("Hello expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae, your hobby is Neuron Staking")'
  mockIC.run_test(
      "demo_from_wire_one_arg", demo_from_wire_one_arg,
      "4449444c0001710e4e6575726f6e205374616b696e67",
      "4449444c0001716348656c6c6f206578706d742d67747873772d696e66746a2d747461626a2d71687035732d6e6f7a75702d6e3362626f2d6b377a766e2d64673468652d6b6e6163332d6c61652c20796f757220686f626279206973204e6575726f6e205374616b696e67",
      silent_on_trap, my_principal);

  // '("Neuron Staking", 3000 : nat64)' ->
  // '("Hello expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae, you earned 3000 ICP from your hobby, Neuron Staking")'
  mockIC.run_test(
      "demo_from_wire_multiple_args", demo_from_wire_multiple_args,
      "4449444c000271780e4e6575726f6e205374616b696e67b80b000000000000",
      "4449444c0001717a48656c6c6f206578706d742d67747873772d696e66746a2d747461626a2d71687035732d6e6f7a75702d6e3362626f2d6b377a766e2d64673468652d6b6e6163332d6c61652c20796f75206561726e65642033303030204943502066726f6d20796f757220686f6262792c204e6575726f6e205374616b696e67",
      silent_on_trap, my_principal);

  // '()' -> '("The current time in nanoseconds: 1684261743015817922 (2023-5-16 18:29:3)")'
  mockIC.run_test(
      "demo_time", demo_time, "4449444c0000",
      "",    // Don't assert, by passing expected_response=""
      false, // Activate debug_print, by passing silent_on_trap=false
      my_principal);

  // '()' -> '()'
  mockIC.run_test("demo_to_wire_no_arg", demo_to_wire_no_arg, "4449444c0000",
                  "4449444c0000", silent_on_trap, my_principal);

  // '("Neuron Staking")' ->
  // '("Hello expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae, your hobby is Neuron Staking")'
  mockIC.run_test(
      "demo_to_wire_one_arg", demo_to_wire_one_arg,
      "4449444c0001710e4e6575726f6e205374616b696e67",
      "4449444c0001716348656c6c6f206578706d742d67747873772d696e66746a2d747461626a2d71687035732d6e6f7a75702d6e3362626f2d6b377a766e2d64673468652d6b6e6163332d6c61652c20796f757220686f626279206973204e6575726f6e205374616b696e67",
      silent_on_trap, my_principal);

  // '("Neuron Staking", 3000 : nat64)' ->
  // '("expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae", "Neuron Staking", 3000 : nat64, "ICP")'
  mockIC.run_test(
      "demo_to_wire_multiple_args", demo_to_wire_multiple_args,
      "4449444c000271780e4e6575726f6e205374616b696e67b80b000000000000",
      "4449444c0004717178713f6578706d742d67747873772d696e66746a2d747461626a2d71687035732d6e6f7a75702d6e3362626f2d6b377a766e2d64673468652d6b6e6163332d6c61650e4e6575726f6e205374616b696e67b80b00000000000003494350",
      silent_on_trap, my_principal);

  // Verify that a this method traps
  // '()' -> trap message
  mockIC.run_trap_test("demo_trap", demo_trap, "4449444c0000", silent_on_trap,
                       my_principal);

  // -----------------------------------------------------------------------------
  // IC_API - utilities

  // '()' -> '()'
  mockIC.run_test(
      "demo_string_to_int128", demo_string_to_int128, "4449444c0000",
      "4449444c0000",
      false, // Activate debug_print, by passing silent_on_trap=false
      my_principal);

  // '()' -> '()'
  mockIC.run_test(
      "demo_to_string_128", demo_to_string_128, "4449444c0000", "4449444c0000",
      false, // Activate debug_print, by passing silent_on_trap=false
      my_principal);

  // -----------------------------------------------------------------------------
  // returns 1 if any tests failed
  return mockIC.test_summary();
}