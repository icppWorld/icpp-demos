// Demo of a counter per caller
// - Using orthogonal persistence for std::unordered_map<std::string, uint64_t>
// - The key is the principal of the caller

#include "counter4me.h"
#include "ic_api.h"

#include <iostream>
#include <vector>

// State of the Smart Contract, using Orthogonal Persistence
std::unordered_map<std::string, uint64_t> counter4me;

// -----------------------------------------------------------------------
// Helper functions

void print_counter4me(std::string calling_function, std::string caller) {
  std::cout << "Called by " + calling_function << std::endl;
  std::cout << "caller = " + caller << std::endl;
  std::cout << "counter4me[caller] = " + std::to_string(counter4me[caller])
            << std::endl;
  std::cout << "Full content of counter4me:" << std::endl;
  std::cout << "- counter4me.size() = " + std::to_string(counter4me.size())
            << std::endl;
  for (const auto &pair : counter4me) {
    std::cout << "- counter4me[\"" + pair.first +
                     "\"] = " + std::to_string(pair.second)
              << std::endl;
  }
}

// -----------------------------------------------------------------------
// Canister endpoints

// Resets the counter for the caller's principle instance and overwrites it with a new value
void write_counter4me() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();
  std::string principal = caller.get_text();

  // The value of the counter coming in from the wire
  uint64_t counter;
  ic_api.from_wire(CandidTypeNat64{&counter});

  // Write the counter for the principal
  counter4me[principal] = counter;

  print_counter4me(std::string(__func__), principal);
  ic_api.to_wire();
}

void inc_counter4me() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();
  std::string principal = caller.get_text();
  ++counter4me[principal];
  print_counter4me(std::string(__func__), principal);
  ic_api.to_wire();
}

void read_counter4me() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();
  std::string principal = caller.get_text();
  print_counter4me(std::string(__func__), principal);
  ic_api.to_wire(CandidTypeNat64{counter4me[principal]});
}