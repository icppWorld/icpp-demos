/* file: src/demo_env_vars.cpp

GREETING is set in icp.yaml (settings.environment_variables); icp-cli adds
PUBLIC_CANISTER_ID:demo on deploy.

$ icp canister call demo demo_env_vars '()' --environment local --query
("GREETING=Hello from icp.yaml. PUBLIC_CANISTER_ID:demo=4caro-hl777-77775-aaaba-cai. getenv(\"GREETING\") returns \"Hello from icp.yaml\".")

*/
#include "demo_env_vars.h"
#include "ic_api.h"

#include <cstdlib>
#include <string>

void demo_env_vars() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);

  std::string msg;
  for (const auto &[name, value] : IC_API::get_env_vars()) {
    msg += name + "=" + value + ". ";
  }

  // getenv() reads the same variables
  const char *greeting = getenv("GREETING");
  msg += std::string("getenv(\"GREETING\") returns ") +
         (greeting ? "\"" + std::string(greeting) + "\"" : "NULL") + ".";
  ic_api.to_wire(CandidTypeText(msg));
}
