/* file: src/demo_candid_type_text.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_text '("demo A" : text)'
("demo A")
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_text received value 'demo A'

$ dfx canister call --type idl --output idl demo demo_candid_type_texts '("demo A" : text, "demo B" : text)'
("demo A", "demo B")
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_texts received values 'demo A' & 'demo B'

*/
#include "demo_candid_type_text.h"

#include <string>

#include "ic_api.h"

void demo_candid_type_text() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();

  std::string in{""};
  ic_api.from_wire(CandidTypeText{&in});
  IC_API::debug_print("Method " + std::string(__func__) + " received value '" +
                      in + "'");

  ic_api.to_wire(CandidTypeText{in});
}

void demo_candid_type_texts() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();

  std::string in1{""};
  std::string in2{""};
  std::vector<CandidType> args_in;
  args_in.push_back(CandidTypeText(&in1));
  args_in.push_back(CandidTypeText(&in2));
  ic_api.from_wire(args_in);

  IC_API::debug_print("Method " + std::string(__func__) + " received values '" +
                      in1 + "' & '" + in2 + "'");

  std::vector<CandidType> args_out;
  args_out.push_back(CandidTypeText(in1));
  args_out.push_back(CandidTypeText(in2));
  ic_api.to_wire(args_out);
}