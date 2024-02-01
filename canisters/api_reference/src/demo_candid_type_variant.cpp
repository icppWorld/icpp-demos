/* file: https://github.com/icppWorld/icpp-demos/tree/main/canisters/api_reference/src/demo_candid_type_variant.cpp

$ dfx canister call --type idl --output idl demo demo_candid_type_variant '(variant {"field 2" = 0.1 : float32;})'
(variant { field 2 = 0.1 : float32;})
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_variant
    received a variant with label: field 2

    field 2  - float       value '0.100000

$ dfx canister call --type idl --output idl demo demo_candid_type_variants '(variant {"field 1" = true : bool;}, variant {"field 2" = 0.1 : float32;})'
(variant {"field 1" = true : bool;}, variant {"field 2" = 0.1 : float32;})
-> check the console of the local network. The canister will print:
   [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] Method demo_candid_type_variants

    received a variant with label: field 2

    field 2  - float       value '0.100000

    received another variant with label: field 2

    field 2  - float       value '0.100000

*/
#include "demo_candid_type_variant.h"

#include <string>

#include "ic_api.h"

void demo_candid_type_variant() {
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

  std::string label{""};
  CandidTypeVariant v_in(&label);
  v_in.append("field 1", CandidTypeBool{&f1});
  v_in.append("field 2", CandidTypeFloat32{&f2});
  v_in.append("field 3", CandidTypeFloat64{&f3});
  v_in.append("field 4", CandidTypeInt8{&f4});
  v_in.append("field 5", CandidTypeInt16{&f5});
  v_in.append("field 6", CandidTypeInt32{&f6});
  v_in.append("field 7", CandidTypeInt64{&f7});
  v_in.append("field 8", CandidTypeInt{&f8});
  v_in.append("field 9", CandidTypeNat8{&f9});
  v_in.append("field 10", CandidTypeNat16{&f10});
  v_in.append("field A", CandidTypeNat32{&fa});
  v_in.append("field B", CandidTypeNat64{&fb});
  v_in.append("field C", CandidTypeNat{&fc});
  v_in.append("field D", CandidTypePrincipal{&fd});
  v_in.append("field E", CandidTypeText{&fe});
  ic_api.from_wire(v_in);

  // ---------------------------------------------------------------------------
  // Debug print of the values

  std::string msg;
  msg.append("Method " + std::string(__func__) +
             "\n received a variant with label: " + label + "\n");

  if (label == "field 1") {
    msg.append("\n field 1  - bool        value '" + std::to_string(f1));
  } else if (label == "field 2") {
    msg.append("\n field 2  - float       value '" + std::to_string(f2));
  } else if (label == "field 3") {
    msg.append("\n field 3  - double      value '" + std::to_string(f3));
  } else if (label == "field 4") {
    msg.append("\n field 4  - int8_t      value '" + std::to_string(f4));
  } else if (label == "field 5") {
    msg.append("\n field 5  - int16_t     value '" + std::to_string(f5));
  } else if (label == "field 6") {
    msg.append("\n field 6  - int32_t     value '" + std::to_string(f6));
  } else if (label == "field 7") {
    msg.append("\n field 7  - int64_t     value '" + std::to_string(f7));
  } else if (label == "field 8") {
    msg.append("\n field 8  - __int128_t  value '" + IC_API::to_string_128(f8));
  } else if (label == "field 9") {
    msg.append("\n field 9  - uint8_t     value '" + std::to_string(f9));
  } else if (label == "field 10") {
    msg.append("\n field 10 - uint16_t    value '" + std::to_string(f10));
  } else if (label == "field A") {
    msg.append("\n field A  - uint32_t    value '" + std::to_string(fa));
  } else if (label == "field B") {
    msg.append("\n field B  - uint64_t    value '" + std::to_string(fb));
  } else if (label == "field C") {
    msg.append("\n field C  - __uint128_t value '" + IC_API::to_string_128(fc));
  } else if (label == "field D") {
    msg.append("\n field D  - std::string value '" + fd);
  } else if (label == "field E") {
    msg.append("\n field E  - std::string value '" + fe);
  }

  IC_API::debug_print(msg);

  // ---------------------------------------------------------------------------
  // Return the data
  CandidTypeVariant v_out{label};
  if (label == "field 1") {
    v_out.append("field 1", CandidTypeBool{f1});
  } else if (label == "field 2") {
    v_out.append("field 2", CandidTypeFloat32{f2});
  } else if (label == "field 3") {
    v_out.append("field 3", CandidTypeFloat64{f3});
  } else if (label == "field 4") {
    v_out.append("field 4", CandidTypeInt8{f4});
  } else if (label == "field 5") {
    v_out.append("field 5", CandidTypeInt16{f5});
  } else if (label == "field 6") {
    v_out.append("field 6", CandidTypeInt32{f6});
  } else if (label == "field 7") {
    v_out.append("field 7", CandidTypeInt64{f7});
  } else if (label == "field 8") {
    v_out.append("field 8", CandidTypeInt{f8});
  } else if (label == "field 9") {
    v_out.append("field 9", CandidTypeNat8{f9});
  } else if (label == "field 10") {
    v_out.append("field 10", CandidTypeNat16{f10});
  } else if (label == "field A") {
    v_out.append("field A", CandidTypeNat32{fa});
  } else if (label == "field B") {
    v_out.append("field B", CandidTypeNat64{fb});
  } else if (label == "field C") {
    v_out.append("field C", CandidTypeNat{fc});
  } else if (label == "field D") {
    v_out.append("field D", CandidTypePrincipal{fd});
  } else if (label == "field E") {
    v_out.append("field E", CandidTypeText{fe});
  }
  ic_api.to_wire(v_out);
}

void demo_candid_type_variants() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  // ---------------------------------------------------------------------------
  // Get the data from the wire for two variants

  // variant a
  bool f1a{false};
  float f2a{0.0};

  std::string labela{""};
  CandidTypeVariant va_in(&labela);
  va_in.append("field 1", CandidTypeBool{&f1a});
  va_in.append("field 2", CandidTypeFloat32{&f2a});

  // variant b
  bool f1b{false};
  float f2b{0.0};

  std::string labelb{""};
  CandidTypeVariant vb_in(&labelb);
  vb_in.append("field 1", CandidTypeBool{&f1b});
  vb_in.append("field 2", CandidTypeFloat32{&f2b});

  CandidArgs args_in;
  args_in.append(va_in);
  args_in.append(vb_in);
  ic_api.from_wire(args_in);

  // ---------------------------------------------------------------------------
  // Debug print of the values

  // variant a
  std::string msg;
  msg.append("Method " + std::string(__func__) +
             "\n received a variant with label: " + labela + "\n");

  if (labela == "field 1") {
    msg.append("\n field 1  - bool        value '" + std::to_string(f1a));
  } else if (labela == "field 2") {
    msg.append("\n field 2  - float       value '" + std::to_string(f2a));
  }

  // variant b
  msg.append("\n\n received another variant with label: " + labelb + "\n");

  if (labelb == "field 1") {
    msg.append("\n field 1  - bool        value '" + std::to_string(f1b));
  } else if (labelb == "field 2") {
    msg.append("\n field 2  - float       value '" + std::to_string(f2b));
  }

  IC_API::debug_print(msg);

  // ---------------------------------------------------------------------------
  // Return the data

  // variant a
  CandidTypeVariant va_out{labela};
  if (labela == "field 1") {
    va_out.append("field 1", CandidTypeBool{f1a});
  } else if (labela == "field 2") {
    va_out.append("field 2", CandidTypeFloat32{f2a});
  }

  // variant b
  CandidTypeVariant vb_out{labelb};
  if (labelb == "field 1") {
    vb_out.append("field 1", CandidTypeBool{f1b});
  } else if (labelb == "field 2") {
    vb_out.append("field 2", CandidTypeFloat32{f2b});
  }

  CandidArgs args_out;
  args_out.append(va_out);
  args_out.append(vb_out);
  ic_api.to_wire(args_out);
}