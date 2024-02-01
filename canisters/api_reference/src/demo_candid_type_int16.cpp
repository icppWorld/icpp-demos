/* file: https://github.com/icppWorld/icpp-demos/tree/main/canisters/api_reference/src/demo_candid_type_int16.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_int16 '(101 : int16)'
(101 : int16)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_int16 received value '101'

$ dfx canister call --type idl --output idl demo demo_candid_type_int16s '(101 : int16, -102 : int16)'
(101 : int16, -102 : int16)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_int16s received values '101' & '-102'

*/
#include "demo_candid_type_int16.h"

#include <string>

#include "ic_api.h"

void demo_candid_type_int16() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  int16_t in{0};
  ic_api.from_wire(CandidTypeInt16{&in});
  IC_API::debug_print("Method " + std::string(__func__) + " received value '" +
                      std::to_string(in) + "'");
  ic_api.to_wire(CandidTypeInt16{in});
}

void demo_candid_type_int16s() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  int16_t in1{0};
  int16_t in2{0};
  CandidArgs args_in;
  args_in.append(CandidTypeInt16(&in1));
  args_in.append(CandidTypeInt16(&in2));
  ic_api.from_wire(args_in);

  IC_API::debug_print("Method " + std::string(__func__) + " received values '" +
                      std::to_string(in1) + "' & '" + std::to_string(in2) +
                      "'");

  CandidArgs args_out;
  args_out.append(CandidTypeInt16(in1));
  args_out.append(CandidTypeInt16(in2));
  ic_api.to_wire(args_out);
}