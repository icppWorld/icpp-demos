// Demo of a counter per caller
// - Using orthogonal persistence for std::unordered_map<std::string, uint64_t>
// - The key is the principal of the caller

#include "counter4me.h"
#include "ic_api.h"

#include <vector>

// State of the Smart Contract, using Orthogonal Persistence
// For Orthogonal Persistence to work, the data must be managed at a global level

// Self managed pointer to a wrapped std::unordered_map
class counter4me {
public:
  std::unordered_map<std::string, uint64_t> umap;
};

counter4me *p_counter4me{nullptr};

// -----------------------------------------------------------------------
// Helper functions

// Create a counter4me instance if not yet done
void new_memory() {
  if (p_counter4me == nullptr) {
    IC_API::debug_print(std::string(__func__) +
                        ": Creating counter4me Instance.");
    p_counter4me = new (std::nothrow) counter4me();
    if (p_counter4me == nullptr) {
      IC_API::trap("Allocation of p_counter4me failed");
    }
  }
}

void delete_memory() {
  if (p_counter4me) {
    delete p_counter4me;
    p_counter4me = nullptr;
  }
}

void print_counter4me(std::string calling_function, std::string caller) {
  IC_API::debug_print("Called by " + calling_function);
  IC_API::debug_print("caller = " + caller);
  if (p_counter4me) {
    IC_API::debug_print("p_counter4me->umap[caller] = " +
                        std::to_string(p_counter4me->umap[caller]));
    IC_API::debug_print("Full content of umap:");
    IC_API::debug_print("- p_counter4me->umap.size() = " +
                        std::to_string(p_counter4me->umap.size()));
    for (const auto &pair : p_counter4me->umap) {
      IC_API::debug_print("- p_counter4me->umap[\"" + pair.first +
                          "\"] = " + std::to_string(pair.second));
    }
  } else {
    IC_API::debug_print("p_counter4me is null");
  }
}

// -----------------------------------------------------------------------
// Canister endpoints

// See: https://internetcomputer.org/docs/current/references/ic-interface-spec#system-api-init
// - This method will be called automatically during INITIAL deployment
void canister_init() {
  IC_API ic_api(CanisterInit{std::string(__func__)}, false);

  // Create a counter4me instance
  new_memory();
}

// Resets the counter for the caller's principle instance and overwrites it with a new value
void write_counter4me() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();
  std::string principal = caller.get_text();

  // The value of the counter coming in from the wire
  uint64_t counter;
  ic_api.from_wire(CandidTypeNat64{&counter});

  // Write the counter for the principal
  p_counter4me->umap[principal] = counter;

  print_counter4me(std::string(__func__), principal);
  ic_api.to_wire();
}

void inc_counter4me() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();
  std::string principal = caller.get_text();
  if (p_counter4me) ++p_counter4me->umap[principal];
  print_counter4me(std::string(__func__), principal);
  ic_api.to_wire();
}

void read_counter4me() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();
  std::string principal = caller.get_text();
  print_counter4me(std::string(__func__), principal);
  ic_api.to_wire(CandidTypeNat64{p_counter4me->umap[principal]});
}