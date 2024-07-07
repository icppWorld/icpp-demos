/* file: https://github.com/icppWorld/icpp-demos/tree/main/canisters/api_reference/src/demo_candid_type_int32.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_int32 '(101 : int32)'
(101 : int32)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_int32 received value '101'

$ dfx canister call --type idl --output idl demo demo_candid_type_int32s '(101 : int32, -102 : int32)'
(101 : int32, -102 : int32)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_int32s received values '101' & '-102'

*/
#include "demo_candid_type_int32.h"

#include <iostream>
#include <string>

#include "ic_api.h"

void demo_candid_type_int32() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  int32_t in{0};
  ic_api.from_wire(CandidTypeInt32{&in});
  std::cout << "Method " + std::string(__func__) + " received value '" +
                   std::to_string(in) + "'"
            << std::endl;
  ic_api.to_wire(CandidTypeInt32{in});
}

void demo_candid_type_int32s() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  int32_t in1{0};
  int32_t in2{0};
  CandidArgs args_in;
  args_in.append(CandidTypeInt32(&in1));
  args_in.append(CandidTypeInt32(&in2));
  ic_api.from_wire(args_in);

  std::cout << "Method " + std::string(__func__) + " received values '" +
                   std::to_string(in1) + "' & '" + std::to_string(in2) + "'"
            << std::endl;

  CandidArgs args_out;
  args_out.append(CandidTypeInt32(in1));
  args_out.append(CandidTypeInt32(in2));
  ic_api.to_wire(args_out);
}