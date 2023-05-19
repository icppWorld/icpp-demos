/* file: src/demo_candid_type_nat8.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_nat8 '(101 : nat8)'
(101 : nat8)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_nat8 received value '101'

$ dfx canister call --type idl --output idl demo demo_candid_type_nat8s '(101 : nat8, 102 : nat8)'
(101 : nat8, 102 : nat8)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_nat8s received values '101' & '102'

*/
#include "demo_candid_type_nat8.h"

#include <string>

#include "ic_api.h"

void demo_candid_type_nat8() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();

  uint8_t in{0};
  ic_api.from_wire(CandidTypeNat8{&in});
  IC_API::debug_print("Method " + std::string(__func__) + " received value '" +
                      std::to_string(in) + "'");
  ic_api.to_wire(CandidTypeNat8{in});
}

void demo_candid_type_nat8s() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();

  uint8_t in1{0};
  uint8_t in2{0};
  std::vector<CandidType> args_in;
  args_in.push_back(CandidTypeNat8(&in1));
  args_in.push_back(CandidTypeNat8(&in2));
  ic_api.from_wire(args_in);

  IC_API::debug_print("Method " + std::string(__func__) + " received values '" +
                      std::to_string(in1) + "' & '" + std::to_string(in2) +
                      "'");

  std::vector<CandidType> args_out;
  args_out.push_back(CandidTypeNat8(in1));
  args_out.push_back(CandidTypeNat8(in2));
  ic_api.to_wire(args_out);
}