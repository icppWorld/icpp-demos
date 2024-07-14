/* file: src/demo_debug_print.cpp

$ dfx canister call --type idl --output idl demo demo_debug_print '()'
...nothing is printed here

-> check the console of the local network. The canister will print:
   Hello expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae

-> when deployed to IC's mainnet, nothing is printed.

*/
#include "demo_debug_print.h"
#include "ic_api.h"
#include <iostream>

void demo_debug_print() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  // You can use this
  std::cout << "Hello " + caller.get_text() << std::endl;

  // Or this.
  IC_API::debug_print("Hello " + caller.get_text());

  ic_api.from_wire();
  ic_api.to_wire();
}