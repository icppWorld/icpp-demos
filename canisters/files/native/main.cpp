// Main entry point for a native debug executable.
// Build it with: `icpp build-native` from the parent folder where 'icpp.toml' resides

#include "main.h"

#include <iostream>

#include "../src/download.h"
#include "../src/io.h"

// The Mock IC
#include "mock_ic.h"

int main() {
  MockIC mockIC(true);

  // -----------------------------------------------------------------------------
  // Configs for the tests:

  // The pretend principals of the caller
  std::string my_principal{
      "expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae"};
  std::string anonymous_principal{"2vxsx-fae"};

  bool silent_on_trap = true;

  // -----------------------------------------------------------------------------
  // '()' -> '(variant { Ok = record { data = vec { "Hello "; "from the "; "internal data file!";}; header = "_data_";} })'
  mockIC.run_test(
      "write_read_during_query", write_read_during_query, "4449444c0000",
      "4449444c036c02aaac8d9304018d9380e80f716d716b01bc8a0100010200030648656c6c6f200966726f6d207468652013696e7465726e616c20646174612066696c6521065f646174615f",
      silent_on_trap, my_principal);

  // '()' -> '(variant { Ok = record { data = vec { "Hello "; "from the "; "internal data file!";}; header = "_data_";} })'
  mockIC.run_test(
      "write_read_during_update", write_read_during_update, "4449444c0000",
      "4449444c036c02aaac8d9304018d9380e80f716d716b01bc8a0100010200030648656c6c6f200966726f6d207468652013696e7465726e616c20646174612066696c6521065f646174615f",
      silent_on_trap, my_principal);

  // download the file with ~1.9Mb chunk (1.9x1024x1024 bytes)
  // '(record { filename="internal_data_file"; chunksize=2000000 : nat64; offset=0 : nat64 })' ->
  // '(variant { Err = variant { Other = "file_download_chunk: ERROR: failed to open ifstream for file internal_data_file" } })'
  mockIC.run_test(
      "file_download_chunk", file_download_chunk,
      "4449444c016c0393affe810678c7dda8bb0771aec3faa40b780100000000000000000012696e7465726e616c5f646174615f66696c6580841e0000000000",
      "4449444c036c0582e1b793047eed8c8bae040193affe810678bdbaf9d50778aec3faa40b786d7b6b01bc8a010001020001405f646174615f060000000000000048656c6c6f20090000000000000066726f6d20746865201300000000000000696e7465726e616c20646174612066696c6521000000000000000040000000000000004000000000000000",
      silent_on_trap, my_principal);

  // returns 1 if any tests failed
  return mockIC.test_summary();
}