/* file: src/demo_cycles.cpp

$ icp canister call demo demo_cycles_balances '()' --environment local
("Cycle balance: 3091662937500 total, 3091592937500 liquid (spendable)")

$ icp canister call demo demo_burn_cycles '()' --environment local
("Burned 1000000 cycles. New balance: 3091661937500")

*/
#include "demo_cycles.h"
#include "ic_api.h"

void demo_cycles_balances() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);

  // The total balance, and the part of it the canister can spend without
  // dropping below its freezing threshold.
  __uint128_t total = ic_api.get_canister_self_cycle_balance();
  __uint128_t liquid = ic_api.get_canister_liquid_cycle_balance();

  std::string msg;
  msg.append("Cycle balance: " + IC_API::to_string_128(total) + " total, " +
             IC_API::to_string_128(liquid) + " liquid (spendable)");
  ic_api.to_wire(CandidTypeText(msg));
}

void demo_burn_cycles() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);

  // Burns up to the requested amount from the canister's own balance and
  // returns how much was actually burned.
  __uint128_t burned = ic_api.burn_cycles(1000000);
  __uint128_t balance = ic_api.get_canister_self_cycle_balance();

  std::string msg;
  msg.append("Burned " + IC_API::to_string_128(burned) +
             " cycles. New balance: " + IC_API::to_string_128(balance));
  ic_api.to_wire(CandidTypeText(msg));
}
