// Main entry point for a native debug executable.
// Build it with: `icpp build-native` from the parent folder where 'icpp.toml' resides

#include "main.h"

#include <iostream>

#include "../src/memory.h"

// The Mock IC
#include "mock_ic.h"

int main() {
  MockIC mockIC(true);

  // The pretend principals of the caller
  std::string my_principal{
      "expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae"};

  bool silent_on_trap = true;

  // --------------------------------------------------------------------

  // '()' -> '()'
  mockIC.run_test("change_memory", change_memory, "4449444c0000", "",
                  silent_on_trap, my_principal);

  // '()' -> '()'
  mockIC.run_test("print_memory", print_memory, "4449444c0000", "",
                  silent_on_trap, my_principal);

  // -----------------------------------------------------------------------------
  // returns 1 if any tests failed
  return mockIC.test_summary();
}
