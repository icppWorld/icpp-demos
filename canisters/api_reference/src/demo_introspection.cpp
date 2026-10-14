/* file: src/demo_introspection.cpp

$ icp canister call demo demo_introspection '()' --environment local
("Canister version 2, running, replicated execution, on subnet w5bul-v73ez-ptacz-wphit-tyxt7-saait-4di22-ws2wo-dtv4x-2rmts-7ae with 13 nodes. The IC root key has 133 bytes. 312114 instructions executed so far.")

$ icp canister call demo demo_introspection_query '()' --environment local --query
("Non-replicated execution. Caller info: 0 bytes, no signer.")

Without --query, icp sends the call as an update, so the query method
executes replicated:
$ icp canister call demo demo_introspection_query '()' --environment local
("Replicated execution. Caller info: 0 bytes, no signer.")

*/
#include "demo_introspection.h"
#include "ic_api.h"

#include <string>

void demo_introspection() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);

  std::string status;
  switch (ic_api.get_canister_status()) {
  case IC_API::CanisterStatus::Running:
    status = "running";
    break;
  case IC_API::CanisterStatus::Stopping:
    status = "stopping";
    break;
  case IC_API::CanisterStatus::Stopped:
    status = "stopped";
    break;
  }

  // An update call executes on every node of the subnet (replicated).
  std::string msg =
      "Canister version " + std::to_string(ic_api.get_canister_version()) +
      ", " + status + ", " +
      (IC_API::in_replicated_execution() ? "replicated" : "non-replicated") +
      " execution, on subnet " + ic_api.get_subnet_self().get_text() +
      " with " + std::to_string(ic_api.get_subnet_node_count()) +
      " nodes. The IC root key has " +
      std::to_string(ic_api.get_root_key().size()) + " bytes. " +
      std::to_string(IC_API::performance_counter()) +
      " instructions executed so far.";
  ic_api.to_wire(CandidTypeText(msg));
}

void demo_introspection_query() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);

  // A query call executes on a single node (non-replicated). The root key
  // is not available here.
  std::string msg =
      std::string(IC_API::in_replicated_execution() ? "Replicated"
                                                    : "Non-replicated") +
      " execution. Caller info: " +
      std::to_string(ic_api.get_caller_info_data().size()) + " bytes, " +
      (ic_api.get_caller_info_signer().has_value() ? "signed by a canister"
                                                   : "no signer") +
      ".";
  ic_api.to_wire(CandidTypeText(msg));
}
