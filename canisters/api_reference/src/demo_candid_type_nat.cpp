/* file: https://github.com/icppWorld/icpp-demos/tree/main/canisters/api_reference/src/demo_candid_type_nat.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_nat '(101 : nat)'
(101 : nat)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_nat received value '101'

$ dfx canister call --type idl --output idl demo demo_candid_type_nats '(101 : nat, 102 : nat)'
(101 : nat, 102 : nat)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_nats received values '101' & '102'

*/
#include "demo_candid_type_nat.h"

#include <iostream>
#include <string>

#include "ic_api.h"

void demo_candid_type_nat() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  __uint128_t in{0};
  ic_api.from_wire(CandidTypeNat{&in});
  std::cout << "Method " + std::string(__func__) + " received value '" +
                   IC_API::to_string_128(in) + "'"
            << std::endl;
  ic_api.to_wire(CandidTypeNat{in});
}

void demo_candid_type_nats() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  __uint128_t in1{0};
  __uint128_t in2{0};
  CandidArgs args_in;
  args_in.append(CandidTypeNat(&in1));
  args_in.append(CandidTypeNat(&in2));
  ic_api.from_wire(args_in);

  std::cout << "Method " + std::string(__func__) + " received values '" +
                   IC_API::to_string_128(in1) + "' & '" +
                   IC_API::to_string_128(in2) + "'"
            << std::endl;

  CandidArgs args_out;
  args_out.append(CandidTypeNat(in1));
  args_out.append(CandidTypeNat(in2));
  ic_api.to_wire(args_out);
}