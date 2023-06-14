/* file: src/demo_trap.cpp

$ dfx canister call --type idl --output idl demo demo_trap '()'
Error: Failed query call.
Caused by: Failed query call.
  The Replica returned an error: code 5, message: "IC0503: Canister bkyz2-fmaaa-aaaaa-qaaaq-cai trapped explicitly:
  Hello expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae
  This is a trap demo."

*/
#include "demo_trap.h"
#include "ic_api.h"

void demo_trap() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  IC_API::trap("\n   Hello " + caller.get_text() + "\n   This is a trap demo.");
}