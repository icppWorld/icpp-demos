// Demo of multiple counters, using orthogonal persistence for std::vector<uint64_t>

#include "counters.h"
#include "ic_api.h"

#include <iostream>
#include <vector>

// State of the Smart Contract, using Orthogonal Persistence
std::vector<uint64_t> counters;

// -----------------------------------------------------------------------
// Helper functions

void print_counters(std::string calling_function) {
  std::cout << "Called by " + calling_function << std::endl;
  for (auto &value : counters) {
    std::cout << "value = " + std::to_string(value) << std::endl;
  }
}

// -----------------------------------------------------------------------
// Canister endpoints

// Resets the counters and overwrites it with new counters
void write_counters() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);

  ic_api.from_wire(CandidTypeVecNat64{&counters});
  print_counters(std::string(__func__));
  ic_api.to_wire();
}

// Adds more counters
void additional_counters() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  std::vector<uint64_t> v;
  ic_api.from_wire(CandidTypeVecNat64{&v});
  counters.insert(counters.end(), v.begin(), v.end());
  print_counters(std::string(__func__));
  ic_api.to_wire();
}

// Increments all counters by 1
void inc_counters() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  for (auto &value : counters) {
    ++value;
  }
  print_counters(std::string(__func__));
  ic_api.to_wire();
}

// Return the counters to the caller
void read_counters() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  print_counters(std::string(__func__));
  ic_api.to_wire(CandidTypeVecNat64{counters});
}