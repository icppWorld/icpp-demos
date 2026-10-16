// Main entry point for a native debug executable.
// Build it with: `icpp build-native` from the parent folder where 'icpp.toml'
// resides.
//
// The Mock IC answers the ledger with the responses set with expect_call.

#include "main.h"

#include <iostream>

#include "../src/icrc1_client.h"

// The Mock IC
// clang-format off
#include "ic_api.h"
#include "icpp_hooks.h"
#include "mock_ic.h"
#include "ic0.h"
// clang-format on

int main() {
  bool exit_on_fail = true;
  MockIC mockIC(exit_on_fail);
  std::string caller{
      "expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae"};
  const std::string LEDGER{"ryjl3-tyaaa-aaaaa-aaaba-cai"};
  // (principal "ryjl3-tyaaa-aaaaa-aaaba-cai")
  const std::string P_LEDGER{"4449444c000168010a00000000000000020101"};
  // (principal "ryjl3-...", principal "aaaaa-aa", 1_000_000 : nat)
  const std::string TRANSFER_ARGS{
      "4449444c000368687d010a000000000000000201010100c0843d"};
  // Candid hex of the ledger's replies, from the reference encoder
  mockIC.expect_call(LEDGER, "icrc1_symbol",
                     MockIC::MockResponse::reply("4449444c0001710454455354"));
  mockIC.expect_call(LEDGER, "icrc1_fee",
                     MockIC::MockResponse::reply("4449444c00017d904e"));
  mockIC.expect_call(LEDGER, "icrc1_decimals",
                     MockIC::MockResponse::reply("4449444c00017b08"));
  mockIC.expect_call(LEDGER, "icrc1_balance_of",
                     MockIC::MockResponse::reply("4449444c00017d8094ebdc03"));

  // '(ledger)' -> '("TEST: fee 10000, 8 decimals")'
  mockIC.run_test("token_info", token_info, P_LEDGER,
                  "4449444c0001711b544553543a206665652031303030302c203820646563"
                  "696d616c73",
                  true, caller);
  // '(ledger)' -> '(1_000_000_000 : nat)'
  mockIC.run_test("balance", balance, P_LEDGER, "4449444c00017d8094ebdc03",
                  true, caller);

  // icrc1_transfer: Ok, and the errors
  mockIC.expect_call(
      LEDGER, "icrc1_transfer",
      MockIC::MockResponse::reply("4449444c016b01bc8a017d01000001"));
  // '(...)' -> '("Ok: block 1")'
  mockIC.run_test("transfer Ok", transfer, TRANSFER_ARGS,
                  "4449444c0001710b4f6b3a20626c6f636b2031", true, caller);
  mockIC.expect_call(
      LEDGER, "icrc1_transfer",
      MockIC::MockResponse::reply(
          "4449444c036b01c5fed201016b01eb9cdbd50f026c019cbab69c027d0100000005"));
  // '(...)' -> '("Err: InsufficientFunds, balance 5")'
  mockIC.run_test("transfer InsufficientFunds", transfer, TRANSFER_ARGS,
                  "4449444c000171214572723a20496e73756666696369656e7446756e6473"
                  "2c2062616c616e63652035",
                  true, caller);
  mockIC.expect_call(
      LEDGER, "icrc1_transfer",
      MockIC::MockResponse::reply(
          "4449444c036b01c5fed201016b01eb82a89704026c018bbdf29b017d0100000001"));
  // '(...)' -> '("Err: Duplicate of block 1")'
  mockIC.run_test("transfer Duplicate", transfer, TRANSFER_ARGS,
                  "4449444c000171194572723a204475706c6963617465206f6620626c6f"
                  "636b2031",
                  true, caller);
  // A timeout is retried once, with the same created_at_time
  mockIC.expect_call(LEDGER, "icrc1_transfer", MockIC::MockResponse::timeout());
  mockIC.run_test("transfer, timed out twice", transfer, TRANSFER_ARGS, "",
                  true, caller);

  // returns 1 if any tests failed
  return mockIC.test_summary();
}
