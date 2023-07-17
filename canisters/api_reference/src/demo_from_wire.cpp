/* file: src/demo_from_wire.cpp

$ dfx canister call --type idl --output idl demo demo_from_wire_no_arg '()'


$ dfx canister call --type idl --output idl demo demo_from_wire_one_arg '("Neuron Staking")'
("Hello expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae, your hobby is Neuron Staking")

$ dfx canister call --type idl --output idl demo demo_from_wire_multiple_args '("Neuron Staking", 3000 : nat64)'
("Hello expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae, you earned 3000 ICP from your hobby, Neuron Staking")

*/
#include "demo_from_wire.h"
#include "ic_api.h"

void demo_from_wire_no_arg() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  ic_api.from_wire();
  ic_api.to_wire();
}

void demo_from_wire_one_arg() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  std::string hobby{""};
  ic_api.from_wire(CandidTypeText{&hobby});

  std::string msg;
  msg.append("Hello " + caller.get_text() + ", ");
  msg.append("your hobby is " + hobby);

  ic_api.to_wire(CandidTypeText(msg));
}

void demo_from_wire_multiple_args() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  std::string hobby{""};
  uint64_t num_icp{0};
  CandidArgs args_in;
  args_in.append(CandidTypeText(&hobby));
  args_in.append(CandidTypeNat64(&num_icp));
  ic_api.from_wire(args_in);

  std::string msg;
  msg.append("Hello " + caller.get_text() + ", ");
  msg.append("you earned " + std::to_string(num_icp) +
             " ICP from your hobby, " + hobby);
  ic_api.to_wire(CandidTypeText(msg));
}