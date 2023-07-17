/* file: src/demo_candid_type_bool.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_bool '(true)'
(true)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_bool received value '1'

$ dfx canister call --type idl --output idl demo demo_candid_type_bools '(true, false)'
(true, false)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_bools received values '1' & '0'

*/
#include "demo_candid_type_bool.h"

#include <string>

#include "ic_api.h"

void demo_candid_type_bool() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  bool in{false};
  ic_api.from_wire(CandidTypeBool{&in});
  IC_API::debug_print("Method " + std::string(__func__) + " received value '" +
                      std::to_string(in) + "'");
  ic_api.to_wire(CandidTypeBool{in});
}

void demo_candid_type_bools() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  bool in1{false};
  bool in2{false};
  CandidArgs args_in;
  args_in.append(CandidTypeBool(&in1));
  args_in.append(CandidTypeBool(&in2));
  ic_api.from_wire(args_in);

  IC_API::debug_print("Method " + std::string(__func__) + " received values '" +
                      std::to_string(in1) + "' & '" + std::to_string(in2) +
                      "'");

  CandidArgs args_out;
  args_out.append(CandidTypeBool(in1));
  args_out.append(CandidTypeBool(in2));
  ic_api.to_wire(args_out);
}