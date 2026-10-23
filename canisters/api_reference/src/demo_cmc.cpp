/* file: src/demo_cmc.cpp

Creates a canister on a subnet of your choice, through the cycles minting
canister (CMC). The management canister's create_canister always creates on
this canister's own subnet.

$ icp canister call demo demo_create_on_subnet '(principal "<subnet>", 2_000_000_000_000 : nat)' --environment ic
(
  "created ryjl3-tyaaa-aaaaa-aaaba-cai",
)

*/
#include "demo_cmc.h"
#include "ic_api.h"

#include <string>

// The cycles minting canister, on mainnet
const char *CMC = "rkp4c-7iaaa-aaaaa-aaaca-cai";

// '(subnet, cycles)' -> '("created <principal>")'. The attached cycles pay for
// the creation; the rest is the new canister's balance. They come from this
// canister's balance, so only a controller may call it, with at most 10T.
IC_Async demo_create_on_subnet_async() {
  IC_API ic_api(CanisterUpdate{"demo_create_on_subnet"}, false);
  std::string subnet;
  __uint128_t cycles{0};
  CandidArgs args;
  args.append(CandidTypePrincipal{&subnet});
  args.append(CandidTypeNat{&cycles});
  ic_api.from_wire(args);
  if (!ic_api.is_controller(ic_api.get_caller())) {
    IC_API::trap("demo_create_on_subnet: only a controller may call it");
  }
  if (cycles > 10'000'000'000'000) {
    IC_API::trap("demo_create_on_subnet: at most 10T cycles");
  }

  // record { subnet_selection : opt variant { Subnet : record { subnet } } }
  // settings is left out: this canister becomes the controller
  CandidTypeRecord choice;
  choice.append("subnet", CandidTypePrincipal{subnet});
  CandidTypeRecord arg;
  arg.append("subnet_selection",
             CandidTypeOptVariant{CandidTypeVariant{"Subnet", choice}});

  // The call carries cycles, and the CMC is part of the IC: an unbounded wait,
  // so the cycles can't be lost on a timeout
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuser-defined-warnings"
  IC_Call call =
      IC_Call::unbounded_wait(CandidTypePrincipal{CMC}, "create_canister");
#pragma clang diagnostic pop
  IC_CallResult<IC_CallReply> r =
      co_await call.with_arg(arg).with_cycles(cycles);
  if (!r) {
    ic_api.to_wire(CandidTypeText{"the call failed: " + r.error().to_string()});
    co_return;
  }

  // variant { Ok : principal;
  //           Err : variant { Refunded : record { refund_amount : nat;
  //                                               create_error : text } } }
  std::string label, created, err_label, create_error;
  __uint128_t refund_amount{0};
  CandidTypeRecord refunded;
  refunded.append("refund_amount", CandidTypeNat{&refund_amount});
  refunded.append("create_error", CandidTypeText{&create_error});
  CandidTypeVariant err{&err_label};
  err.append("Refunded", refunded);
  CandidTypeVariant result{&label};
  result.append("Ok", CandidTypePrincipal{&created});
  result.append("Err", err);
  r->decode(result);

  // A failed creation is a reply, with the cycles refunded
  ic_api.to_wire(CandidTypeText{
      label == "Ok"
          ? "created " + created
          : "not created: " + create_error + " (refunded " +
                ICPP_HOOKS::to_string_128(refund_amount) + " cycles)"});
}
void demo_create_on_subnet() { demo_create_on_subnet_async(); }
