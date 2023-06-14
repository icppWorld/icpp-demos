/* file: src/demo_candid_type_int.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_int '(101 : int)'
(101 : int)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_int received value '101'

$ dfx canister call --type idl --output idl demo demo_candid_type_ints '(101 : int, -102 : int)'
(101 : int, -102 : int)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_ints received values '101' & '-102'

*/
#include "demo_candid_type_int.h"

#include <string>

#include "ic_api.h"

void demo_candid_type_int() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  __int128_t in{0};
  ic_api.from_wire(CandidTypeInt{&in});
  IC_API::debug_print("Method " + std::string(__func__) + " received value '" +
                      IC_API::to_string_128(in) + "'");
  ic_api.to_wire(CandidTypeInt{in});
}

void demo_candid_type_ints() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  __int128_t in1{0};
  __int128_t in2{0};
  std::vector<CandidType> args_in;
  args_in.push_back(CandidTypeInt(&in1));
  args_in.push_back(CandidTypeInt(&in2));
  ic_api.from_wire(args_in);

  IC_API::debug_print("Method " + std::string(__func__) + " received values '" +
                      IC_API::to_string_128(in1) + "' & '" +
                      IC_API::to_string_128(in2) + "'");

  std::vector<CandidType> args_out;
  args_out.push_back(CandidTypeInt(in1));
  args_out.push_back(CandidTypeInt(in2));
  ic_api.to_wire(args_out);
}