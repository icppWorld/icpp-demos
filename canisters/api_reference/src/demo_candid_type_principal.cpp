/* file: https://github.com/icppWorld/icpp-demos/tree/main/canisters/api_reference/src/demo_candid_type_principal.cpp

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

#include <iostream>
#include <string>

#include "ic_api.h"

// Whitelisted principals, saved in Orthogonal Persisted Memory
std::vector<std::string> whitelisted_principals = {
    "expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae", // User
    "iineg-fibai-bqibi-ga4ea-searc-ijrif-iwc4m-bsibb-eirsi-jjge4-ucs", // User
    "6uwoh-vaaaa-aaaag-amema-cai", // Another canister
};

void demo_candid_type_principal() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);

  // This demo shows how to implement whitelisting of users.

  // 1. Get the caller's authenticated principal
  // - The calling message was signed using the caller's private key
  // - The IC verified the signature using the corresponding public key
  CandidTypePrincipal caller = ic_api.get_caller();

  // 2. Check if the user is anonymous
  // If the user is not anonymous, that means that the user is authenticated
  // with Internet Identity or other mechanisms that assign a unique
  // principal ID.
  if (caller.is_anonymous()) {
    std::cout << "User is not logged in " << std::endl;
  } else {
    std::cout << "User is logged in " << std::endl;
  }

  // 3. Get the caller's principal id in text format
  std::string principal_id_caller = caller.get_text();
  std::cout << "User's principal id is " << principal_id_caller << std::endl;

  // 4. Check if the caller's principal is whitelisted using std::find
  auto it = std::find(whitelisted_principals.begin(),
                      whitelisted_principals.end(), principal_id_caller);
  if (it != whitelisted_principals.end()) {
    std::cout << "User is whitelisted." << std::endl;
  } else {
    std::cout << "User is not whitelisted." << std::endl;
  }

  // This call expects as argument a string in the format of a Candid principal
  // Note that this is NOT the caller's principal ID, it is just an argument.
  // For example, if the caller wants to send some ICP to another principal,
  // the caller's principal id is authenticated as above, while the receiving
  // principal's id is passed in as argument:
  // - Value follows the rules for text representation of a Candid principal
  // - It's just a string, nothing more. Not authenticated by IC using keys
  std::string principal_id_from_arg{""};
  ic_api.from_wire(CandidTypePrincipal{&principal_id_from_arg});
  std::cout << "Principal id passed by argument is " + principal_id_from_arg
            << std::endl;

  // For QA purposes, send the principal id back to the wire
  ic_api.to_wire(CandidTypePrincipal{principal_id_from_arg});
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

  std::cout << "Method " + std::string(__func__) + " received values '" + in1 +
                   "' & '" + in2 + "'"
            << std::endl;

  CandidArgs args_out;
  args_out.append(CandidTypePrincipal(in1));
  args_out.append(CandidTypePrincipal(in2));
  ic_api.to_wire(args_out);
}