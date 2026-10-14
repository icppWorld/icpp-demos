/* file: src/demo_cost.cpp

$ icp canister call demo demo_cost '()' --environment local --query
("Calling greet with 100 bytes: 42102517000 cycles. Creating a canister: 500000000000 cycles. An HTTPS outcall: 158340000 cycles. An Ed25519 signature with test_key_1: 10000000000 cycles.")

*/
#include "demo_cost.h"
#include "ic_api.h"

#include <string>

void demo_cost() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);

  auto cycles = [](__uint128_t v) { return IC_API::to_string_128(v); };

  // A call to "greet" with a 100-byte argument
  std::string msg =
      "Calling greet with 100 bytes: " + cycles(IC_API::cost_call(5, 100)) +
      " cycles. ";
  msg += "Creating a canister: " + cycles(IC_API::cost_create_canister()) +
         " cycles. ";
  // An HTTPS outcall: 1 kB request, at most 10 kB response
  msg +=
      "An HTTPS outcall: " + cycles(IC_API::cost_http_request(1'000, 10'000)) +
      " cycles. ";

  IC_API::SignCost sign = IC_API::cost_sign_with_schnorr(
      "test_key_1", IC_API::SchnorrAlgorithm::Ed25519);
  if (sign.error == IC_API::SignCostError::None) {
    msg += "An Ed25519 signature with test_key_1: " + cycles(sign.cycles) +
           " cycles.";
  } else {
    msg += "test_key_1 cannot sign with Ed25519 here.";
  }
  ic_api.to_wire(CandidTypeText(msg));
}
