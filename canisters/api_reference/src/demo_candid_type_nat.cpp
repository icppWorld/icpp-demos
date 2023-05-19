/* file: src/demo_candid_type_nat.cpp

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

#include <string>

#include "ic_api.h"

void demo_candid_type_nat() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();

  __uint128_t in{0};
  ic_api.from_wire(CandidTypeNat{&in});
  IC_API::debug_print("Method " + std::string(__func__) + " received value '" +
                      IC_API::to_string_128(in) + "'");
  ic_api.to_wire(CandidTypeNat{in});
}

void demo_candid_type_nats() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();

  __uint128_t in1{0};
  __uint128_t in2{0};
  std::vector<CandidType> args_in;
  args_in.push_back(CandidTypeNat(&in1));
  args_in.push_back(CandidTypeNat(&in2));
  ic_api.from_wire(args_in);

  IC_API::debug_print("Method " + std::string(__func__) + " received values '" +
                      IC_API::to_string_128(in1) + "' & '" +
                      IC_API::to_string_128(in2) + "'");

  std::vector<CandidType> args_out;
  args_out.push_back(CandidTypeNat(in1));
  args_out.push_back(CandidTypeNat(in2));
  ic_api.to_wire(args_out);
}