/* file: src/demo_candid_type_int64.cpp

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

#include <string>

#include "ic_api.h"

void demo_candid_type_int64() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();

  int64_t in{0};
  ic_api.from_wire(CandidTypeInt64{&in});
  IC_API::debug_print("Method " + std::string(__func__) + " received value '" +
                      std::to_string(in) + "'");
  ic_api.to_wire(CandidTypeInt64{in});
}

void demo_candid_type_int64s() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();

  int64_t in1{0};
  int64_t in2{0};
  std::vector<CandidType> args_in;
  args_in.push_back(CandidTypeInt64(&in1));
  args_in.push_back(CandidTypeInt64(&in2));
  ic_api.from_wire(args_in);

  IC_API::debug_print("Method " + std::string(__func__) + " received values '" +
                      std::to_string(in1) + "' & '" + std::to_string(in2) +
                      "'");

  std::vector<CandidType> args_out;
  args_out.push_back(CandidTypeInt64(in1));
  args_out.push_back(CandidTypeInt64(in2));
  ic_api.to_wire(args_out);
}