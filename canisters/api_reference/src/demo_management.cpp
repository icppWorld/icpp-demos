/* file: src/demo_management.cpp

$ icp canister call demo demo_raw_rand '()' --environment local
(
  "32 random bytes: dac93bd0b5ca3d5e6b0a54beb06961c9edf8b5038a02c57e5d1f4d45de4cd97f",
)

$ icp canister call demo demo_sign '("icpp")' --environment local
(
  "public key 026b3965713aecb522045d7fae01bb6aca6ff2dc3954c2ed13e7848a25db3d40f2, signature e8bc1ec8741f59a8af6081c1c692903bd38f1890fbbbc0bf8a0b1b972bbba9112c68d871b6d023df7dd4f4c6c2817d6db684e11af1db50376d2d4c0dc8b0bc51",
)

*/
#include "demo_management.h"
#include "ic_api.h"

#include <string>

namespace {
std::string hex(const IC_Blob &bytes) {
  const char *digits = "0123456789abcdef";
  std::string s;
  for (uint8_t b : bytes) {
    s += digits[b >> 4];
    s += digits[b & 0xf];
  }
  return s;
}
} // namespace

// 32 random bytes from the management canister
IC_Async demo_raw_rand_async() {
  IC_API ic_api(CanisterUpdate{"demo_raw_rand"}, false);
  ic_api.from_wire();
  IC_CallResult<IC_Blob> random = co_await IC_Management::raw_rand();
  ic_api.to_wire(CandidTypeText{random ? "32 random bytes: " + hex(*random)
                                       : "raw_rand failed: " +
                                             random.error().to_string()});
}
void demo_raw_rand() { demo_raw_rand_async(); }

// Signs a 32-byte digest of a message with threshold ECDSA. The cycles of the
// signature are attached for you. test_key_1 exists on mainnet and on a
// local network.
IC_Async demo_sign_async() {
  IC_API ic_api(CanisterUpdate{"demo_sign"}, false);
  std::string message;
  ic_api.from_wire(CandidTypeText{&message});

  // An illustrative XOR fold, not a cryptographic hash: a real application
  // signs the SHA-256 of the message.
  IC_Blob message_hash(32, 0);
  for (size_t i = 0; i < message.size(); ++i)
    message_hash[i % 32] ^= (uint8_t)message[i];

  IC_EcdsaKeyId key{IC_API::EcdsaCurve::Secp256k1, "test_key_1"};
  std::vector<IC_Blob> derivation_path{{'d', 'e', 'm', 'o'}};
  IC_CallResult<IC_PublicKey> public_key =
      co_await IC_Management::ecdsa_public_key(key, derivation_path);
  IC_CallResult<IC_Blob> signature = co_await IC_Management::sign_with_ecdsa(
      message_hash, derivation_path, key);
  if (!public_key || !signature) {
    ic_api.to_wire(CandidTypeText{
        "signing failed: " + (public_key ? signature.error().to_string()
                                         : public_key.error().to_string())});
    co_return;
  }
  ic_api.to_wire(CandidTypeText{"public key " + hex(public_key->public_key) +
                                ", signature " + hex(*signature)});
}
void demo_sign() { demo_sign_async(); }
