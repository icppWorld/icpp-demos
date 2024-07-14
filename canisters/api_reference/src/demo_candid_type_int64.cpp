/* file: https://github.com/icppWorld/icpp-demos/tree/main/canisters/api_reference/src/demo_candid_type_int64.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_int64 '(101 : int64)'
(101 : int64)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_int64 received value '101'

$ dfx canister call --type idl --output idl demo demo_candid_type_int64s '(101 : int64, -102 : int64)'
(101 : int64, -102 : int64)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_int64s received values '101' & '-102'

*/
#include "demo_candid_type_int64.h"

#include <iostream>
#include <string>

#include "ic_api.h"

void demo_candid_type_int64() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  int64_t in{0};
  ic_api.from_wire(CandidTypeInt64{&in});
  std::cout << "Method " + std::string(__func__) + " received value '" +
                   std::to_string(in) + "'"
            << std::endl;
  ic_api.to_wire(CandidTypeInt64{in});
}

void demo_candid_type_int64s() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  int64_t in1{0};
  int64_t in2{0};
  CandidArgs args_in;
  args_in.append(CandidTypeInt64(&in1));
  args_in.append(CandidTypeInt64(&in2));
  ic_api.from_wire(args_in);

  std::cout << "Method " + std::string(__func__) + " received values '" +
                   std::to_string(in1) + "' & '" + std::to_string(in2) + "'"
            << std::endl;

  CandidArgs args_out;
  args_out.append(CandidTypeInt64(in1));
  args_out.append(CandidTypeInt64(in2));
  ic_api.to_wire(args_out);
}