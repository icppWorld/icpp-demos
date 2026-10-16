/* file: src/icrc1_client.cpp

An ICRC-1 client: it calls the ICRC-1 methods of a ledger canister.

$ icp canister call icrc1_client token_info '(principal "<ledger>")' --environment local
("TEST: fee 10000, 8 decimals")

$ icp canister call icrc1_client balance '(principal "<ledger>")' --environment local
(998_990_000 : nat)

$ icp canister call icrc1_client transfer '(principal "<ledger>", principal "<to>", 1_000_000 : nat)' --environment local
("Ok: block 2")

*/
#include "icrc1_client.h"
#include "ic_api.h"

#include <string>

namespace {
// An ICRC-1 account: record { owner : principal; subaccount : opt blob }.
// Without a subaccount, the field is left out (it is an opt).
CandidTypeRecord account(const std::string &owner) {
  CandidTypeRecord record;
  record.append("owner", CandidTypePrincipal{owner});
  return record;
}

// The first argument of every method: the ledger
CandidTypePrincipal ledger_arg(IC_API &ic_api, CandidArgs &args,
                               std::string &ledger) {
  ic_api.from_wire(args);
  return CandidTypePrincipal{ledger};
}
} // namespace

// Three queries of the ledger, made at the same time with IC_CallAll
IC_Async token_info_async() {
  IC_API ic_api(CanisterUpdate{"token_info"}, false);
  std::string ledger_text;
  CandidArgs args;
  args.append(CandidTypePrincipal{&ledger_text});
  CandidTypePrincipal ledger = ledger_arg(ic_api, args, ledger_text);

  std::vector<IC_CallResult<IC_CallReply>> results = co_await IC_CallAll({
      IC_Call::bounded_wait(ledger, "icrc1_symbol"),
      IC_Call::bounded_wait(ledger, "icrc1_fee"),
      IC_Call::bounded_wait(ledger, "icrc1_decimals"),
  });
  for (IC_CallResult<IC_CallReply> &r : results) {
    if (!r) {
      ic_api.to_wire(CandidTypeText{"failed: " + r.error().to_string()});
      co_return;
    }
  }
  std::string symbol;
  __uint128_t fee{0};
  uint8_t decimals{0};
  results[0]->decode(CandidTypeText{&symbol});
  results[1]->decode(CandidTypeNat{&fee});
  results[2]->decode(CandidTypeNat8{&decimals});
  ic_api.to_wire(CandidTypeText{symbol + ": fee " + IC_API::to_string_128(fee) +
                                ", " + std::to_string(decimals) + " decimals"});
}
void token_info() { token_info_async(); }

// icrc1_balance_of the account of this canister
IC_Async balance_async() {
  IC_API ic_api(CanisterUpdate{"balance"}, false);
  std::string ledger_text;
  CandidArgs args;
  args.append(CandidTypePrincipal{&ledger_text});
  CandidTypePrincipal ledger = ledger_arg(ic_api, args, ledger_text);

  IC_CallResult<IC_CallReply> r =
      co_await IC_Call::bounded_wait(ledger, "icrc1_balance_of")
          .with_arg(account(ic_api.get_canister_self().get_text()));
  __uint128_t balance{0};
  r->decode(CandidTypeNat{&balance});
  ic_api.to_wire(CandidTypeNat{balance});
}
void balance() { balance_async(); }

// icrc1_transfer from this canister's account. The call is a bounded-wait
// call: when it times out (SysUnknown), the transfer may or may not have
// happened. It is retried with the same created_at_time, which makes the
// ledger see the retry as the same transfer: if the first one went through,
// the ledger answers Duplicate instead of transferring twice.
IC_Async transfer_async() {
  IC_API ic_api(CanisterUpdate{"transfer"}, false);
  std::string ledger_text, to;
  __uint128_t amount{0};
  CandidArgs args;
  args.append(CandidTypePrincipal{&ledger_text});
  args.append(CandidTypePrincipal{&to});
  args.append(CandidTypeNat{&amount});
  CandidTypePrincipal ledger = ledger_arg(ic_api, args, ledger_text);

  // record { to : Account; amount : nat; created_at_time : opt nat64 }
  // The other fields - from_subaccount, fee, memo - are opts, left out.
  CandidTypeRecord transfer_arg;
  transfer_arg.append("to", account(to));
  transfer_arg.append("amount", CandidTypeNat{amount});
  transfer_arg.append("created_at_time", CandidTypeOptNat64{IC_API::time()});

  IC_CallResult<IC_CallReply> r =
      co_await IC_Call::bounded_wait(ledger, "icrc1_transfer")
          .with_arg(transfer_arg);
  if (!r && r.error().reject_code == IC_RejectCode::SysUnknown) {
    r = co_await IC_Call::bounded_wait(ledger, "icrc1_transfer")
            .with_arg(transfer_arg);
  }
  if (!r) {
    ic_api.to_wire(CandidTypeText{"failed: " + r.error().to_string()});
    co_return;
  }

  // variant { Ok : nat; Err : TransferError }
  std::string label, error_label, message;
  __uint128_t block{0}, expected_fee{0}, min_burn_amount{0}, balance{0},
      duplicate_of{0}, error_code{0};
  uint64_t ledger_time{0};
  CandidTypeRecord bad_fee, bad_burn, insufficient_funds, created_in_future,
      duplicate, generic_error;
  bad_fee.append("expected_fee", CandidTypeNat{&expected_fee});
  bad_burn.append("min_burn_amount", CandidTypeNat{&min_burn_amount});
  insufficient_funds.append("balance", CandidTypeNat{&balance});
  created_in_future.append("ledger_time", CandidTypeNat64{&ledger_time});
  duplicate.append("duplicate_of", CandidTypeNat{&duplicate_of});
  generic_error.append("error_code", CandidTypeNat{&error_code});
  generic_error.append("message", CandidTypeText{&message});
  CandidTypeVariant transfer_error{&error_label};
  transfer_error.append("BadFee", bad_fee);
  transfer_error.append("BadBurn", bad_burn);
  transfer_error.append("InsufficientFunds", insufficient_funds);
  transfer_error.append("TooOld", CandidTypeNull{});
  transfer_error.append("CreatedInFuture", created_in_future);
  transfer_error.append("TemporarilyUnavailable", CandidTypeNull{});
  transfer_error.append("Duplicate", duplicate);
  transfer_error.append("GenericError", generic_error);
  CandidTypeVariant result{&label};
  result.append("Ok", CandidTypeNat{&block});
  result.append("Err", transfer_error);
  r->decode(result);

  std::string text;
  if (label == "Ok") {
    text = "Ok: block " + IC_API::to_string_128(block);
  } else if (error_label == "InsufficientFunds") {
    text = "Err: InsufficientFunds, balance " + IC_API::to_string_128(balance);
  } else if (error_label == "BadFee") {
    text = "Err: BadFee, expected " + IC_API::to_string_128(expected_fee);
  } else if (error_label == "Duplicate") {
    text = "Err: Duplicate of block " + IC_API::to_string_128(duplicate_of);
  } else if (error_label == "GenericError") {
    text = "Err: GenericError " + IC_API::to_string_128(error_code) + ", " +
           message;
  } else {
    text = "Err: " + error_label;
  }
  ic_api.to_wire(CandidTypeText{text});
}
void transfer() { transfer_async(); }
