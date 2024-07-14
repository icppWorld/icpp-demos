/* file: https://github.com/icppWorld/icpp-demos/tree/main/canisters/api_reference/src/demo_candid_type_opt.cpp

// ----------------------------------------------------------
// The (opt bool) has three possible values:
// - true
// - false
// - no value
// Let's try them all out:

$ dfx canister call --type idl --output idl demo demo_candid_type_opt '(opt (true : bool))'
(opt true)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opt received bool value '1'

$ dfx canister call --type idl --output idl demo demo_candid_type_opt '(opt (false : bool))'
(opt false)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opt received bool value '0'

$ dfx canister call --type idl --output idl demo demo_candid_type_opt '(null)'
(null)
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opt did not receive a bool value

// ----------------------------------------------------------
// The other method has as argument a list of all opt types, eg.

$ dfx canister call --type idl --output idl demo demo_candid_type_opts '(opt (true : bool), opt (0.1 : float32), opt (0.2 : float64), opt (-8 : int8), opt (-16 : int16), opt (-32 : int32), opt (-64 : int64), opt (-128 : int), opt (8 : nat8), opt (16 : nat16), opt (32 : nat32), opt (64 : nat64), opt (128 : nat), opt (principal "2ibo7-dia"), opt ("demo" : text))'
(opt true, opt (0.1 : float32), opt (0.2 : float64), opt (-8 : int8), opt (-16 : int16), opt (-32 : int32), opt (-64 : int64), opt (-128 : int), opt (8 : nat8), opt (16 : nat16), opt (32 : nat32), opt (64 : nat64), opt (128 : nat), opt principal "2ibo7-dia", opt "demo")
-> check the console of the local network. The canister will print:
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received bool value '1'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received float32 value '0.100000'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received float64 value '0.200000'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received int8 value '-8'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received int16 value '-16'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received int32 value '-32'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received int64 value '-64'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received int value '-128'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received nat8 value '8'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received nat16 value '16'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received nat32 value '32'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received nat64 value '64'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received nat value '128'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received principal value '2ibo7-dia'
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_opts received text value 'demo'

*/
#include "demo_candid_type_opt.h"

#include <iostream>
#include <string>

#include "ic_api.h"

void demo_candid_type_opt() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  std::optional<bool> in;
  ic_api.from_wire(CandidTypeOptBool{&in});

  if (in.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received bool value '" +
                     std::to_string(in.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a bool value"
              << std::endl;
  }

  ic_api.to_wire(CandidTypeOptBool{in});
}

void demo_candid_type_opts() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  // ---------------------------------------------------------------------------
  // Get the data from the wire
  std::optional<bool> in_bool;
  std::optional<float> in_float32;
  std::optional<double> in_float64;
  std::optional<int8_t> in_int8;
  std::optional<int16_t> in_int16;
  std::optional<int32_t> in_int32;
  std::optional<int64_t> in_int64;
  std::optional<__int128_t> in_int;
  std::optional<uint8_t> in_nat8;
  std::optional<uint16_t> in_nat16;
  std::optional<uint32_t> in_nat32;
  std::optional<uint64_t> in_nat64;
  std::optional<__uint128_t> in_nat;
  std::optional<std::string> in_principal;
  std::optional<std::string> in_text;

  CandidArgs args_in;
  args_in.append(CandidTypeOptBool{&in_bool});
  args_in.append(CandidTypeOptFloat32{&in_float32});
  args_in.append(CandidTypeOptFloat64{&in_float64});
  args_in.append(CandidTypeOptInt8{&in_int8});
  args_in.append(CandidTypeOptInt16{&in_int16});
  args_in.append(CandidTypeOptInt32{&in_int32});
  args_in.append(CandidTypeOptInt64{&in_int64});
  args_in.append(CandidTypeOptInt{&in_int});
  args_in.append(CandidTypeOptNat8{&in_nat8});
  args_in.append(CandidTypeOptNat16{&in_nat16});
  args_in.append(CandidTypeOptNat32{&in_nat32});
  args_in.append(CandidTypeOptNat64{&in_nat64});
  args_in.append(CandidTypeOptNat{&in_nat});
  args_in.append(CandidTypeOptPrincipal{&in_principal});
  args_in.append(CandidTypeOptText{&in_text});

  ic_api.from_wire(args_in);

  // ---------------------------------------------------------------------------
  // print the data
  if (in_bool.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received bool value '" +
                     std::to_string(in_bool.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a bool value"
              << std::endl;
  }

  if (in_float32.has_value()) {
    std::cout << "Method " + std::string(__func__) +
                     " received float32 value '" +
                     std::to_string(in_float32.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a float32 value"
              << std::endl;
  }

  if (in_float64.has_value()) {
    std::cout << "Method " + std::string(__func__) +
                     " received float64 value '" +
                     std::to_string(in_float64.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a float64 value"
              << std::endl;
  }

  if (in_int8.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received int8 value '" +
                     std::to_string(in_int8.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a int8 value"
              << std::endl;
  }

  if (in_int16.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received int16 value '" +
                     std::to_string(in_int16.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a int16 value"
              << std::endl;
  }

  if (in_int32.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received int32 value '" +
                     std::to_string(in_int32.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a int32 value"
              << std::endl;
  }

  if (in_int64.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received int64 value '" +
                     std::to_string(in_int64.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a int64 value"
              << std::endl;
  }

  if (in_int.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received int value '" +
                     IC_API::to_string_128(in_int.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a int value"
              << std::endl;
  }

  if (in_nat8.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received nat8 value '" +
                     std::to_string(in_nat8.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a nat8 value"
              << std::endl;
  }

  if (in_nat16.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received nat16 value '" +
                     std::to_string(in_nat16.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a nat16 value"
              << std::endl;
  }

  if (in_nat32.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received nat32 value '" +
                     std::to_string(in_nat32.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a nat32 value"
              << std::endl;
  }

  if (in_nat64.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received nat64 value '" +
                     std::to_string(in_nat64.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a nat64 value"
              << std::endl;
  }

  if (in_nat.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received nat value '" +
                     IC_API::to_string_128(in_nat.value()) + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a nat value"
              << std::endl;
  }

  if (in_principal.has_value()) {
    std::cout << "Method " + std::string(__func__) +
                     " received principal value '" + in_principal.value() + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a principal value"
              << std::endl;
  }

  if (in_text.has_value()) {
    std::cout << "Method " + std::string(__func__) + " received text value '" +
                     in_text.value() + "'"
              << std::endl;
  } else {
    std::cout << "Method " + std::string(__func__) +
                     " did not receive a text value"
              << std::endl;
  }

  // ---------------------------------------------------------------------------
  // Return the data
  CandidArgs args_out;
  args_out.append(CandidTypeOptBool{in_bool});
  args_out.append(CandidTypeOptFloat32{in_float32});
  args_out.append(CandidTypeOptFloat64{in_float64});
  args_out.append(CandidTypeOptInt8{in_int8});
  args_out.append(CandidTypeOptInt16{in_int16});
  args_out.append(CandidTypeOptInt32{in_int32});
  args_out.append(CandidTypeOptInt64{in_int64});
  args_out.append(CandidTypeOptInt{in_int});
  args_out.append(CandidTypeOptNat8{in_nat8});
  args_out.append(CandidTypeOptNat16{in_nat16});
  args_out.append(CandidTypeOptNat32{in_nat32});
  args_out.append(CandidTypeOptNat64{in_nat64});
  args_out.append(CandidTypeOptNat{in_nat});
  args_out.append(CandidTypeOptPrincipal{in_principal});
  args_out.append(CandidTypeOptText{in_text});
  ic_api.to_wire(args_out);
}