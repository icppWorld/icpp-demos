/* file: src/demo_to_string_128.cpp

$ dfx canister call --type idl --output idl demo demo_to_string_128 '()'
...nothing is printed here

-> check the console of the local network. The canister will print:
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] v1 =101
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] v2 =102
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] v3 =-103

-> when deployed to IC's mainnet, nothing is printed.

*/
#include "demo_to_string_128.h"

#include <optional>
#include <string>

#include "ic_api.h"

void demo_to_string_128() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();

  // -------------------------------------------------------------------------
  // Numbers smaller than uint64_t & int64_t can be initialized with a literal
  __uint128_t v1{101};
  __int128_t v2{102};
  __int128_t v3{-103};

  // To create a string, use the IC_API utility method `to_string_128`
  IC_API::debug_print("v1 =" + IC_API::to_string_128(v1));
  IC_API::debug_print("v2 =" + IC_API::to_string_128(v2));
  IC_API::debug_print("v3 =" + IC_API::to_string_128(v3));

  // ----------------------------------------------------------------------------
  // Numbers larger than uint64_t & int64_t can NOT be initialized with a literal
  // See `demo_string_to_int128.cpp`

  ic_api.from_wire();
  ic_api.to_wire();
}