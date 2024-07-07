/* file: https://github.com/icppWorld/icpp-demos/tree/main/canisters/api_reference/src/demo_candid_type_float64.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_float64 '(0.1 : float64)'
(0.1 : float64)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_float64 received value '0.100000'

$ dfx canister call --type idl --output idl demo demo_candid_type_float64s '(0.1 : float64, -1.2 : float64)'
(0.1 : float64, -1.2 : float64)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_float64s received values '0.100000' & '-1.200000'

*/
#include "demo_candid_type_float64.h"

#include <iostream>
#include <string>

#include "ic_api.h"

void demo_candid_type_float64() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  double in{0.0};
  ic_api.from_wire(CandidTypeFloat64{&in});
  std::cout << "Method " + std::string(__func__) + " received value '" +
                   std::to_string(in) + "'"
            << std::endl;
  ic_api.to_wire(CandidTypeFloat64{in});
}

void demo_candid_type_float64s() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  double in1{0.0};
  double in2{0.0};
  CandidArgs args_in;
  args_in.append(CandidTypeFloat64(&in1));
  args_in.append(CandidTypeFloat64(&in2));
  ic_api.from_wire(args_in);

  std::cout << "Method " + std::string(__func__) + " received values '" +
                   std::to_string(in1) + "' & '" + std::to_string(in2) + "'"
            << std::endl;

  CandidArgs args_out;
  args_out.append(CandidTypeFloat64(in1));
  args_out.append(CandidTypeFloat64(in2));
  ic_api.to_wire(args_out);
}