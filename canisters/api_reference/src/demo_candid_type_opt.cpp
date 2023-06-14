/* file: src/demo_candid_type_opt.cpp

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

#include <string>

#include "ic_api.h"

void demo_candid_type_opt() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  std::optional<bool> in;
  ic_api.from_wire(CandidTypeOptBool{&in});

  if (in.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received bool value '" + std::to_string(in.value()) +
                        "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a bool value");
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

  std::vector<CandidType> args_in;
  args_in.push_back(CandidTypeOptBool{&in_bool});
  args_in.push_back(CandidTypeOptFloat32{&in_float32});
  args_in.push_back(CandidTypeOptFloat64{&in_float64});
  args_in.push_back(CandidTypeOptInt8{&in_int8});
  args_in.push_back(CandidTypeOptInt16{&in_int16});
  args_in.push_back(CandidTypeOptInt32{&in_int32});
  args_in.push_back(CandidTypeOptInt64{&in_int64});
  args_in.push_back(CandidTypeOptInt{&in_int});
  args_in.push_back(CandidTypeOptNat8{&in_nat8});
  args_in.push_back(CandidTypeOptNat16{&in_nat16});
  args_in.push_back(CandidTypeOptNat32{&in_nat32});
  args_in.push_back(CandidTypeOptNat64{&in_nat64});
  args_in.push_back(CandidTypeOptNat{&in_nat});
  args_in.push_back(CandidTypeOptPrincipal{&in_principal});
  args_in.push_back(CandidTypeOptText{&in_text});

  ic_api.from_wire(args_in);

  // ---------------------------------------------------------------------------
  // debug_print the data
  if (in_bool.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received bool value '" +
                        std::to_string(in_bool.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a bool value");
  }

  if (in_float32.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received float32 value '" +
                        std::to_string(in_float32.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a float32 value");
  }

  if (in_float64.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received float64 value '" +
                        std::to_string(in_float64.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a float64 value");
  }

  if (in_int8.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received int8 value '" +
                        std::to_string(in_int8.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a int8 value");
  }

  if (in_int16.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received int16 value '" +
                        std::to_string(in_int16.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a int16 value");
  }

  if (in_int32.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received int32 value '" +
                        std::to_string(in_int32.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a int32 value");
  }

  if (in_int64.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received int64 value '" +
                        std::to_string(in_int64.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a int64 value");
  }

  if (in_int.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received int value '" +
                        IC_API::to_string_128(in_int.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a int value");
  }

  if (in_nat8.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received nat8 value '" +
                        std::to_string(in_nat8.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a nat8 value");
  }

  if (in_nat16.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received nat16 value '" +
                        std::to_string(in_nat16.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a nat16 value");
  }

  if (in_nat32.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received nat32 value '" +
                        std::to_string(in_nat32.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a nat32 value");
  }

  if (in_nat64.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received nat64 value '" +
                        std::to_string(in_nat64.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a nat64 value");
  }

  if (in_nat.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received nat value '" +
                        IC_API::to_string_128(in_nat.value()) + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a nat value");
  }

  if (in_principal.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received principal value '" + in_principal.value() +
                        "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a principal value");
  }

  if (in_text.has_value()) {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " received text value '" + in_text.value() + "'");
  } else {
    IC_API::debug_print("Method " + std::string(__func__) +
                        " did not receive a text value");
  }

  // ---------------------------------------------------------------------------
  // Return the data
  std::vector<CandidType> args_out;
  args_out.push_back(CandidTypeOptBool{in_bool});
  args_out.push_back(CandidTypeOptFloat32{in_float32});
  args_out.push_back(CandidTypeOptFloat64{in_float64});
  args_out.push_back(CandidTypeOptInt8{in_int8});
  args_out.push_back(CandidTypeOptInt16{in_int16});
  args_out.push_back(CandidTypeOptInt32{in_int32});
  args_out.push_back(CandidTypeOptInt64{in_int64});
  args_out.push_back(CandidTypeOptInt{in_int});
  args_out.push_back(CandidTypeOptNat8{in_nat8});
  args_out.push_back(CandidTypeOptNat16{in_nat16});
  args_out.push_back(CandidTypeOptNat32{in_nat32});
  args_out.push_back(CandidTypeOptNat64{in_nat64});
  args_out.push_back(CandidTypeOptNat{in_nat});
  args_out.push_back(CandidTypeOptPrincipal{in_principal});
  args_out.push_back(CandidTypeOptText{in_text});
  ic_api.to_wire(args_out);
}