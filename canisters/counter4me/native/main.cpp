// Main entry point for a native debug executable.
// Build it with: `icpp build-native` from the parent folder where 'icpp.toml' resides

#include "main.h"

#include <iostream>

#include "../src/counter4me.h"

// The Mock IC
#include "mock_ic.h"

int main() {
  MockIC mockIC(true);

  // The pretend principals of the caller
  std::string my_principal{
      "expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae"};
  std::string anonymous_principal{"2vxsx-fae"};

  bool silent_on_trap = true;

  // --------------------------------------------------------------------
  // '(10: nat64)' -> '()'
  mockIC.run_test("write_counter4me", write_counter4me,
                  "4449444c0001780a00000000000000", "", silent_on_trap,
                  my_principal);

  // '()' -> '()'
  mockIC.run_test("inc_counter4me", inc_counter4me, "4449444c0000", "",
                  silent_on_trap, my_principal);

  // '()' -> '(11 : nat64)'
  mockIC.run_test("read_counter4me", read_counter4me, "4449444c0000",
                  "4449444c0001780b00000000000000", silent_on_trap,
                  my_principal);

  // '(10: nat64)' -> '()'
  mockIC.run_test("write_counter4me", write_counter4me,
                  "4449444c0001780a00000000000000", "", silent_on_trap,
                  anonymous_principal);

  // '()' -> '()'
  mockIC.run_test("inc_counter4me", inc_counter4me, "4449444c0000", "",
                  silent_on_trap, anonymous_principal);

  // '()' -> '(11 : nat64)'
  mockIC.run_test("read_counter4me", read_counter4me, "4449444c0000",
                  "4449444c0001780b00000000000000", silent_on_trap,
                  anonymous_principal);

  // -----------------------------------------------------------------------------
  // returns 1 if any tests failed
  return mockIC.test_summary();
}
