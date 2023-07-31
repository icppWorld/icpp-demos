// Main entry point for a native debug executable.
// Build it with: `icpp build-native` from the parent folder where 'icpp.toml' resides

#include "main.h"

#include <iostream>

#include "../src/counters.h"

// The Mock IC
#include "mock_ic.h"

int main() {
  MockIC mockIC(true);

  // The pretend principals of the caller
  std::string my_principal{
      "expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae"};

  bool silent_on_trap = true;

  // --------------------------------------------------------------------
  // '()' -> canister_init does not return directly, so skip validation check
  mockIC.run_test("canister_init", canister_init, "4449444c0000", "",
                  silent_on_trap, my_principal);

  // '(vec { 10 : nat64; 10 : nat64 })' -> '()'
  mockIC.run_test("write_counters", write_counters,
                  "4449444c016d780100020a000000000000000a00000000000000", "",
                  silent_on_trap, my_principal);

  // '()' -> '()'
  mockIC.run_test("inc_counters", inc_counters, "4449444c0000", "",
                  silent_on_trap, my_principal);

  // '()' -> '(vec { 11 : nat64; 11 : nat64 })'
  mockIC.run_test("read_counters", read_counters, "4449444c0000",
                  "4449444c016d780100020b000000000000000b00000000000000",
                  silent_on_trap, my_principal);

  // '(vec { 10 : nat64; 10 : nat64 })' -> '()'
  mockIC.run_test("additional_counters", additional_counters,
                  "4449444c016d780100020a000000000000000a00000000000000", "",
                  silent_on_trap, my_principal);

  // '()' -> '()'
  mockIC.run_test("inc_counters", inc_counters, "4449444c0000", "",
                  silent_on_trap, my_principal);

  // '()' -> '(vec { 12 : nat64; 12 : nat64; 11 : nat64; 11 : nat64 })'
  mockIC.run_test(
      "read_counters", read_counters, "4449444c0000",
      "4449444c016d780100040c000000000000000c000000000000000b000000000000000b00000000000000",
      silent_on_trap, my_principal);
}
