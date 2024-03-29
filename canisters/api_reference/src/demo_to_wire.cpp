/* file: src/demo_to_wire.cpp

$ dfx canister call --type idl --output idl demo demo_to_wire_no_arg '()'


$ dfx canister call --type idl --output idl demo demo_to_wire_one_arg '("Neuron Staking")'
("Hello expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae, your hobby is Neuron Staking")

$ dfx canister call --type idl --output idl demo demo_to_wire_multiple_args '("Neuron Staking", 3000 : nat64)'
("expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae", "Neuron Staking", 3_000 : nat64, "ICP")

*/
#include "demo_to_wire.h"
#include "ic_api.h"

void demo_to_wire_no_arg() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  ic_api.from_wire();
  ic_api.to_wire();
}

void demo_to_wire_one_arg() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  std::string hobby{""};
  ic_api.from_wire(CandidTypeText{&hobby});

  std::string msg;
  msg.append("Hello " + caller.get_text() + ", ");
  msg.append("your hobby is " + hobby);

  ic_api.to_wire(CandidTypeText(msg));
}

void demo_to_wire_multiple_args() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  std::string hobby{""};
  uint64_t num_icp{0};
  CandidArgs args_in;
  args_in.append(CandidTypeText(&hobby));
  args_in.append(CandidTypeNat64(&num_icp));
  ic_api.from_wire(args_in);

  CandidArgs args_out;
  args_out.append(CandidTypeText(caller.get_text()));
  args_out.append(CandidTypeText(hobby));
  args_out.append(CandidTypeNat64(num_icp));
  args_out.append(CandidTypeText("ICP"));
  ic_api.to_wire(args_out);
}