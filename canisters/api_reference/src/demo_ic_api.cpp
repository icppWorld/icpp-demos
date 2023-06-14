/* file: src/demo_ic_api.cpp

$ dfx canister call --type idl --output idl demo demo_ic_api '()'

*/
#include "demo_ic_api.h"
#include "ic_api.h"

void demo_ic_api() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();
  ic_api.from_wire();
  ic_api.to_wire();
}