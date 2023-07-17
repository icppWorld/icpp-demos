/* file: src/demo_candid_type_principal.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_principal '(principal "2ibo7-dia")'
(principal "2ibo7-dia")
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_principal received value '2ibo7-dia'

$ dfx canister call --type idl --output idl demo demo_candid_type_principals '(principal "2ibo7-dia", principal "w3gef-eqbai")'
(principal "2ibo7-dia", principal "w3gef-eqbai")
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_principals received values '2ibo7-dia' & 'w3gef-eqbai'

*/
#include "demo_candid_type_principal.h"

#include <string>

#include "ic_api.h"

void demo_candid_type_principal() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);

  // The caller's authenticated principal
  // - The calling message was signed using the caller's private key
  // - The IC verified the signature using the corresponding public key
  CandidTypePrincipal caller = ic_api.get_caller();

  // A string in the format of a Candid principal.
  // - Value follows the rules for text representation of a Candid principal
  // - It's just a string, nothing more. Not authenticated by IC using keys
  std::string in{""};
  ic_api.from_wire(CandidTypePrincipal{&in});
  IC_API::debug_print("Method " + std::string(__func__) + " received value '" +
                      in + "'");

  ic_api.to_wire(CandidTypePrincipal{in});
}

void demo_candid_type_principals() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  std::string in1{""};
  std::string in2{""};
  CandidArgs args_in;
  args_in.append(CandidTypePrincipal(&in1));
  args_in.append(CandidTypePrincipal(&in2));
  ic_api.from_wire(args_in);

  IC_API::debug_print("Method " + std::string(__func__) + " received values '" +
                      in1 + "' & '" + in2 + "'");

  CandidArgs args_out;
  args_out.append(CandidTypePrincipal(in1));
  args_out.append(CandidTypePrincipal(in2));
  ic_api.to_wire(args_out);
}