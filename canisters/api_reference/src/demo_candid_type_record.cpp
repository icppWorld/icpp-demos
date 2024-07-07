/* file: https://github.com/icppWorld/icpp-demos/tree/main/canisters/api_reference/src/demo_candid_type_record.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_record '(record {"field 1" = true : bool; "field 2" = 0.1 : float32; "field 3" = 0.2 : float64; "field 4" = -8 : int8; "field 5" = -16 : int16; "field 6" = -32 : int32; "field 7" = -64 : int64; "field 8" = -128 : int; "field 9" = 8 : nat8; "field 10" = 16 : nat16; "field A" = 32 : nat32; "field B" = 64 : nat64; "field C" = 128 : nat; "field D" = principal "2ibo7-dia"; "field E" = "demo" : text;})'
(record { field 10 = 16 : nat16; field 1 = true; field 2 = 0.1 : float32; field 3 = 0.2 : float64; field 4 = -8 : int8; field 5 = -16 : int16; field 6 = -32 : int32; field 7 = -64 : int64; field 8 = -128 : int; field 9 = 8 : nat8; field A = 32 : nat32; field B = 64 : nat64; field C = 128 : nat; field D = principal "2ibo7-dia"; field E = "demo";})
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_record
 received a record with fields: 

 field 1  - bool        value '1
 field 2  - float       value '0.100000
 field 3  - double      value '0.200000
 field 4  - int8_t      value '-8
 field 5  - int16_t     value '-16
 field 6  - int32_t     value '-32
 field 7  - int64_t     value '-64
 field 8  - __int128_t  value '-128
 field 9  - uint8_t     value '8
 field 10 - uint16_t    value '16
 field A  - uint32_t    value '32
 field B  - uint64_t    value '64
 field C  - __uint128_t value '128
 field D  - std::string value '2ibo7-dia
 field E  - std::string value 'demo'

$ dfx canister call --type idl --output idl demo demo_candid_type_records '(record {"field 1A" = -8 : int8;}, record {"field 2A" = -16 : int16;})'
(record { field 1A = -8 : int8;}, record { field 2A = -16 : int16;})
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_records
 received a record with field:
 field 1A  - int8_t      value '-8
 and      a record with field:
 field 1B  - int16_t     value '-16'

*/
#include "demo_candid_type_record.h"

#include <iostream>
#include <string>

#include "ic_api.h"

void demo_candid_type_record() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  // ---------------------------------------------------------------------------
  // Get the data from the wire
  bool f1{false};
  float f2{0.0};
  double f3{0.0};
  int8_t f4{0};
  int16_t f5{0};
  int32_t f6{0};
  int64_t f7{0};
  __int128_t f8{0};
  uint8_t f9{0};
  uint16_t f10{0};
  uint32_t fa{0};
  uint64_t fb{0};
  __uint128_t fc{0};
  std::string fd{""};
  std::string fe{""};

  CandidTypeRecord r_in;
  r_in.append("field 1", CandidTypeBool{&f1});
  r_in.append("field 2", CandidTypeFloat32{&f2});
  r_in.append("field 3", CandidTypeFloat64{&f3});
  r_in.append("field 4", CandidTypeInt8{&f4});
  r_in.append("field 5", CandidTypeInt16{&f5});
  r_in.append("field 6", CandidTypeInt32{&f6});
  r_in.append("field 7", CandidTypeInt64{&f7});
  r_in.append("field 8", CandidTypeInt{&f8});
  r_in.append("field 9", CandidTypeNat8{&f9});
  r_in.append("field 10", CandidTypeNat16{&f10});
  r_in.append("field A", CandidTypeNat32{&fa});
  r_in.append("field B", CandidTypeNat64{&fb});
  r_in.append("field C", CandidTypeNat{&fc});
  r_in.append("field D", CandidTypePrincipal{&fd});
  r_in.append("field E", CandidTypeText{&fe});
  ic_api.from_wire(r_in);

  // ---------------------------------------------------------------------------
  std::cout << "Method " + std::string(__func__) +
                   "\n received a record with fields: \n" +
                   "\n field 1  - bool        value '" + std::to_string(f1) +
                   "\n field 2  - float       value '" + std::to_string(f2) +
                   "\n field 3  - double      value '" + std::to_string(f3) +
                   "\n field 4  - int8_t      value '" + std::to_string(f4) +
                   "\n field 5  - int16_t     value '" + std::to_string(f5) +
                   "\n field 6  - int32_t     value '" + std::to_string(f6) +
                   "\n field 7  - int64_t     value '" + std::to_string(f7) +
                   "\n field 8  - __int128_t  value '" +
                   IC_API::to_string_128(f8) +
                   "\n field 9  - uint8_t     value '" + std::to_string(f9) +
                   "\n field 10 - uint16_t    value '" + std::to_string(f10) +
                   "\n field A  - uint32_t    value '" + std::to_string(fa) +
                   "\n field B  - uint64_t    value '" + std::to_string(fb) +
                   "\n field C  - __uint128_t value '" +
                   IC_API::to_string_128(fc) +
                   "\n field D  - std::string value '" + fd +
                   "\n field E  - std::string value '" + fe + "'"
            << std::endl;
  // ---------------------------------------------------------------------------

  CandidTypeRecord r_out;
  r_out.append("field 1", CandidTypeBool{f1});
  r_out.append("field 2", CandidTypeFloat32{f2});
  r_out.append("field 3", CandidTypeFloat64{f3});
  r_out.append("field 4", CandidTypeInt8{f4});
  r_out.append("field 5", CandidTypeInt16{f5});
  r_out.append("field 6", CandidTypeInt32{f6});
  r_out.append("field 7", CandidTypeInt64{f7});
  r_out.append("field 8", CandidTypeInt{f8});
  r_out.append("field 9", CandidTypeNat8{f9});
  r_out.append("field 10", CandidTypeNat16{f10});
  r_out.append("field A", CandidTypeNat32{fa});
  r_out.append("field B", CandidTypeNat64{fb});
  r_out.append("field C", CandidTypeNat{fc});
  r_out.append("field D", CandidTypePrincipal{fd});
  r_out.append("field E", CandidTypeText{fe});
  ic_api.to_wire(r_out);
}

void demo_candid_type_records() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  // ---------------------------------------------------------------------------
  // Get the data from the wire
  int8_t f1a{0};
  CandidTypeRecord r1_in;
  r1_in.append("field 1A", CandidTypeInt8{&f1a});

  int16_t f2a{0};
  CandidTypeRecord r2_in;
  r2_in.append("field 2A", CandidTypeInt16{&f2a});

  CandidArgs args_in;
  args_in.append(r1_in);
  args_in.append(r2_in);
  ic_api.from_wire(args_in);

  // ---------------------------------------------------------------------------
  std::cout << "Method " + std::string(__func__) +
                   "\n received a record with field:" +
                   "\n field 1A  - int8_t      value '" + std::to_string(f1a) +
                   "\n and      a record with field:" +
                   "\n field 2A  - int16_t     value '" + std::to_string(f2a) +
                   "'"
            << std::endl;

  // ---------------------------------------------------------------------------
  // Return the data
  CandidTypeRecord r1_out;
  r1_out.append("field 1A", CandidTypeInt8{f1a});

  CandidTypeRecord r2_out;
  r2_out.append("field 2A", CandidTypeInt16{f2a});

  CandidArgs args_out;
  args_out.append(r1_out);
  args_out.append(r2_out);
  ic_api.to_wire(args_out);
}