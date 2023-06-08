// Demo of a counter per caller
// - Using orthogonal persistence for std::unordered_map<std::string, uint64_t>
// - The key is the principal of the caller

#include "counter_for_caller.h"
#include "ic_api.h"

#include <unordered_map>

// For Orthogonal Persistence to work, the data must be managed at a global level
std::pair<std::string, uint64_t> *p_counter_ump = nullptr;
__uint128_t len_counter_ump = 0;

void inc_counter_for_caller() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();
  std::string principal = caller.get_text();

  // Retrieve the unordered map from static memory for orthogonal persistence
  std::unordered_map<std::string, uint64_t> counter_map =
      ic_api.retrieve_unordered_map_orthogonal(p_counter_ump, len_counter_ump);

  // Increment the counter for the principal
  counter_map[principal] += 1;

  // Store it back into static memory for othogonal persistence
  ic_api.store_unordered_map_orthogonal(counter_map, &p_counter_ump,
                                        &len_counter_ump);
}

void read_counter_for_caller() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();
  std::string principal = caller.get_text();

  // Retrieve the unordered map from static memory for orthogonal persistence
  std::unordered_map<std::string, uint64_t> counter_map =
      ic_api.retrieve_unordered_map_orthogonal(p_counter_ump, len_counter_ump);

  ic_api.to_wire(CandidTypeNat64{counter_map[principal]});
}

void write_counter_for_caller() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();
  std::string principal = caller.get_text();

  // The value of the counter coming in from the wire
  uint64_t counter;
  ic_api.from_wire(CandidTypeNat64{&counter});

  // Retrieve the unordered map from static memory for orthogonal persistence
  std::unordered_map<std::string, uint64_t> counter_map =
      ic_api.retrieve_unordered_map_orthogonal(p_counter_ump, len_counter_ump);

  // Write the counter for the principal
  counter_map[principal] = counter;

  // Store it back into static memory for othogonal persistence
  ic_api.store_unordered_map_orthogonal(counter_map, &p_counter_ump,
                                        &len_counter_ump);
}

// Calling a query function does NOT persist between calls. Try it out...
void inc_query_counter_for_caller() {
  IC_API ic_api(false);
  CandidTypePrincipal caller = ic_api.get_caller();
  std::string principal = caller.get_text();

  // Retrieve the unordered map from static memory for orthogonal persistence
  std::unordered_map<std::string, uint64_t> counter_map =
      ic_api.retrieve_unordered_map_orthogonal(p_counter_ump, len_counter_ump);

  // Increment the counter for the principal
  counter_map[principal] += 1;

  // Store it back into static memory for othogonal persistence
  ic_api.store_unordered_map_orthogonal(counter_map, &p_counter_ump,
                                        &len_counter_ump);
}
