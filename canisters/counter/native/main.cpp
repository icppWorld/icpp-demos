// Main entry point for a native debug executable.
// Build it with: `icpp build-native` from the parent folder where 'icpp.toml' resides

#include "main.h"

#include <iostream>

#include "../src/counter.h"

// The Mock IC
#include "global.h"
#include "mock_ic.h"

int main() {
  MockIC mockIC(true);

  // PATCH
  // '()' -> '()'
  mockIC.run_test("inc", inc, "4449444c0000", "");

  //   // '(10: nat)' -> '()'
  //   mockIC.run_test("write", write, "4449444c00017d0a", "");

  //   // '()' -> '()'
  //   mockIC.run_test("inc", inc, "4449444c0000", "");

  //   // '()' -> '(11: nat)'
  //   mockIC.run_test("read", read, "4449444c0000", "4449444c00017d0b");
}
