/* file: src/demo_certified_data.cpp

$ icp canister call demo demo_certified_data_set '()' --environment local
("Certified 32 bytes (use the hash of your application data)")

$ icp canister call demo demo_get_data_certificate '()' --environment local
("The data certificate is present: 621 bytes")

*/
#include "demo_certified_data.h"
#include "ic_api.h"

#include <vector>

void demo_certified_data_set() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);

  // At most 32 bytes can be certified - typically the hash of your
  // application data. The certificate becomes available in query calls
  // after this update call completes.
  std::vector<uint8_t> data(32);
  for (size_t i = 0; i < data.size(); ++i) {
    data[i] = (uint8_t)i;
  }
  ic_api.set_certified_data(data);

  ic_api.to_wire(
      CandidTypeText("Certified 32 bytes (use the hash of your application "
                     "data)"));
}

void demo_get_data_certificate() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);

  // The certificate is only present in a non-replicated query call. A
  // client can verify it against the IC root key, proving the certified
  // data was set by this canister on this subnet.
  std::string msg;
  if (ic_api.data_certificate_present()) {
    std::vector<uint8_t> cert = ic_api.get_data_certificate();
    msg = "The data certificate is present: " + std::to_string(cert.size()) +
          " bytes";
  } else {
    msg = "No data certificate (not a non-replicated query call)";
  }
  ic_api.to_wire(CandidTypeText(msg));
}
