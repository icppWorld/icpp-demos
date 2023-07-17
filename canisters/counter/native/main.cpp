// Main entry point for a native debug executable.
// Build it with: `icpp build-native` from the parent folder where 'icpp.toml' resides

#include "main.h"

#include <iostream>

#include "../src/counter.h"
#include "../src/counter_for_caller.h"
#include "../src/counter_vec.h"

// The Mock IC
#include "mock_ic.h"

int main() {
  MockIC mockIC(true);

  // The pretend principals of the caller
  std::string my_principal{
      "expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae"};

  bool silent_on_trap = true;

  // --------------------------------------------------------------------
  // Test the counter stored in static memory

  // '(10: nat64)' -> '()'
  mockIC.run_test("write", write, "4449444c0001780a00000000000000", "",
                  silent_on_trap, my_principal);

  // '()' -> '()'
  mockIC.run_test("inc", inc, "4449444c0000", "", silent_on_trap, my_principal);

  // '()' -> '(11: nat64)'
  mockIC.run_test("read", read, "4449444c0000",
                  "4449444c0001780b00000000000000", silent_on_trap,
                  my_principal);

  // --------------------------------------------------------------------
  // Test the counter stored in static std::vector

  // '(vec { 10 : nat64; 10 : nat64 })' -> '()'
  mockIC.run_test("write_counter_vec", write_counter_vec,
                  "4449444c016d780100020a000000000000000a00000000000000", "",
                  silent_on_trap, my_principal);

  // '()' -> '()'
  mockIC.run_test("inc_counter_vec", inc_counter_vec, "4449444c0000", "",
                  silent_on_trap, my_principal);

  // '()' -> '(vec { 11 : nat64; 11 : nat64 })'
  mockIC.run_test("read_counter_vec", read_counter_vec, "4449444c0000",
                  "4449444c016d780100020b000000000000000b00000000000000",
                  silent_on_trap, my_principal);

  // --------------------------------------------------------------------
  // Test the counter stored in static std::unordered_map
  // We send a vec of counters, that are stored for the caller's principal

  // '(10: nat64)' -> '()'
  mockIC.run_test("write_counter_for_caller", write_counter_for_caller,
                  "4449444c0001780a00000000000000", "", silent_on_trap,
                  my_principal);

  // '()' -> '()'
  mockIC.run_test("inc_counter_for_caller", inc_counter_for_caller,
                  "4449444c0000", "", silent_on_trap, my_principal);

  // '()' -> '(11: nat64)'
  mockIC.run_test("read_counter_for_caller", read_counter_for_caller,
                  "4449444c0000", "4449444c0001780b00000000000000",
                  silent_on_trap, my_principal);
}
