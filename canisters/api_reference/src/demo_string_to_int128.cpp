/* file: src/demo_string_to_int128.cpp

$ dfx canister call --type idl --output idl demo demo_string_to_int128 '()'
...nothing is printed here

-> check the console of the local network. The canister will print:
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] max__uint128_t=340282366920938463463374607431768211455
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] max__int128_t=170141183460469231731687303715884105727
  [Canister bkyz2-fmaaa-aaaaa-qaaaq-cai] min__int128_t=-170141183460469231731687303715884105727

-> when deployed to IC's mainnet, nothing is printed.

*/
#include "demo_string_to_int128.h"

#include <iostream>
#include <optional>
#include <string>

#include "ic_api.h"

void demo_string_to_int128() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  // ----------------------------------------------------------------------------
  // Numbers larger than uint64_t & int64_t can NOT be initialized with a literal
  // - Use IC_API utility methods `string_to_uint128_t` & `string_to_int128_t`,
  //   to initialize them from a string.
  // - These utility methods return an `std::optional`, which succeeds only if the
  //   conversion is successful.

  std::optional<__uint128_t> max__uint128_t = IC_API::string_to_uint128_t(
      "340282366920938463463374607431768211455"); // 2^128 - 1
  std::optional<__int128_t> max__int128_t = IC_API::string_to_int128_t(
      "170141183460469231731687303715884105727"); // +2^127 - 1
  std::optional<__int128_t> min__int128_t = IC_API::string_to_int128_t(
      "-170141183460469231731687303715884105727"); // -2^127 - 1

  // Now we first check the content of the std::optional, before using to_string_128
  // This is a roundtrip from string -> value -> string
  if (max__uint128_t.has_value()) {
    std::cout << "max__uint128_t=" +
                     IC_API::to_string_128(max__uint128_t.value())
              << std::endl;
  } else {
    IC_API::trap("ERROR: string_to_uint128_t failed for max__uint128_t");
  }

  if (max__int128_t.has_value()) {
    std::cout << "max__int128_t=" + IC_API::to_string_128(max__int128_t.value())
              << std::endl;
  } else {
    IC_API::trap("ERROR: string_to_int128_t failed for max__int128_t");
  }

  if (min__int128_t.has_value()) {
    std::cout << "min__int128_t=" + IC_API::to_string_128(min__int128_t.value())
              << std::endl;
  } else {
    IC_API::trap("ERROR: string_to_int128_t failed for min__int128_t");
  }
  // ----------------------------------------------------------------------------

  ic_api.from_wire();
  ic_api.to_wire();
}