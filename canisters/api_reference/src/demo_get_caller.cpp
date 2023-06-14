/* file: src/demo_get_caller.cpp

$ dfx canister call --type idl --output idl demo demo_get_caller '()'
(Hello! Your principal is expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae)

*/
#include "demo_get_caller.h"
#include "ic_api.h"

void demo_get_caller() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);

  // The caller's authenticated principal
  // - The calling message was signed using the caller's private key
  // - The IC verified the signature using the corresponding public key
  CandidTypePrincipal caller = ic_api.get_caller();

  ic_api.from_wire();

  std::string msg;
  msg.append("Hello! Your principal is ");
  msg.append(caller.get_text());

  ic_api.to_wire(CandidTypeText(msg));
}