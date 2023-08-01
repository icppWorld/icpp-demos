// Main entry point for a native debug executable.
// Build it with: `icpp build-native` from the parent folder where 'icpp.toml' resides

#include "main.h"

#include <iostream>

#include "../src/counter.h"

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

  // -----------------------------------------------------------------------------
  // returns 1 if any tests failed
  return mockIC.test_summary();
}
