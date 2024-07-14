/* file: https://github.com/icppWorld/icpp-demos/tree/main/canisters/api_reference/src/demo_candid_type_nat64.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_nat64 '(101 : nat64)'
(101 : nat64)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_nat64 received value '101'

$ dfx canister call --type idl --output idl demo demo_candid_type_nat64s '(101 : nat64, 102 : nat64)'
(101 : nat64, 102 : nat64)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_nat64s received values '101' & '102'

*/
#include "demo_candid_type_nat64.h"

#include <iostream>
#include <string>

#include "ic_api.h"

void demo_candid_type_nat64() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  uint64_t in{0};
  ic_api.from_wire(CandidTypeNat64{&in});
  std::cout << "Method " + std::string(__func__) + " received value '" +
                   std::to_string(in) + "'"
            << std::endl;
  ic_api.to_wire(CandidTypeNat64{in});
}

void demo_candid_type_nat64s() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  uint64_t in1{0};
  uint64_t in2{0};
  CandidArgs args_in;
  args_in.append(CandidTypeNat64(&in1));
  args_in.append(CandidTypeNat64(&in2));
  ic_api.from_wire(args_in);

  std::cout << "Method " + std::string(__func__) + " received values '" +
                   std::to_string(in1) + "' & '" + std::to_string(in2) + "'"
            << std::endl;

  CandidArgs args_out;
  args_out.append(CandidTypeNat64(in1));
  args_out.append(CandidTypeNat64(in2));
  ic_api.to_wire(args_out);
}