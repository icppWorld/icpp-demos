// Demo of multiple counters, using orthogonal persistence for std::vector<uint64_t>

#include "counters.h"
#include "ic_api.h"

#include <vector>

// State of the Smart Contract, using Orthogonal Persistence
// For Orthogonal Persistence to work, the data must be managed at a global level

// Self managed pointer to a wrapped std::vector
class Counters {
public:
  std::vector<uint64_t> vec;
};

Counters *p_counters{nullptr};

// -----------------------------------------------------------------------
// Helper functions

// Create a Counters instance if not yet done
void new_memory() {
  if (p_counters == nullptr) {
    IC_API::debug_print(std::string(__func__) +
                        ": Creating Counters Instance.");
    p_counters = new (std::nothrow) Counters();
    if (p_counters == nullptr) {
      IC_API::trap("Allocation of p_counters failed");
    }
  }
}

void delete_memory() {
  if (p_counters) {
    delete p_counters;
    p_counters = nullptr;
  }
}

void print_counters(std::string calling_function) {
  IC_API::debug_print("Called by " + calling_function);
  if (p_counters) {
    IC_API::debug_print("p_counters->vec.size() = " +
                        std::to_string(p_counters->vec.size()));
    for (auto &value : p_counters->vec) {
      IC_API::debug_print("value = " + std::to_string(value));
    }
  } else {
    IC_API::debug_print("p_counters is null");
  }
}

// -----------------------------------------------------------------------
// Canister endpoints

// See: https://internetcomputer.org/docs/current/references/ic-interface-spec#system-api-init
// - This method will be called automatically during INITIAL deployment
void canister_init() {
  IC_API ic_api(CanisterInit{std::string(__func__)}, false);

  // Create a Counters instance
  new_memory();
}

// Resets the counters instance and overwrites it with new counters
void write_counters() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);

  delete_memory();
  new_memory();

  ic_api.from_wire(CandidTypeVecNat64{&p_counters->vec});
  print_counters(std::string(__func__));
  ic_api.to_wire();
}

// Adds more counters
void additional_counters() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  std::vector<uint64_t> v;
  ic_api.from_wire(CandidTypeVecNat64{&v});
  if (p_counters)
    p_counters->vec.insert(p_counters->vec.end(), v.begin(), v.end());
  print_counters(std::string(__func__));
  ic_api.to_wire();
}

void inc_counters() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  if (p_counters)
    for (auto &value : p_counters->vec) {
      ++value;
    }
  print_counters(std::string(__func__));
  ic_api.to_wire();
}

void read_counters() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  print_counters(std::string(__func__));
  ic_api.to_wire(CandidTypeVecNat64{p_counters->vec});
}