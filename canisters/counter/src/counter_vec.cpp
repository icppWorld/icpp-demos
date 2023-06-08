// Demo of multiple counters, using orthogonal persistence for std::vector<uint64_t>

#include "counter_vec.h"
#include "ic_api.h"

#include <vector>

// For Orthogonal Persistence to work, the data must be managed at a global level
uint64_t *p_counter_vec = nullptr;
__uint128_t len_counter_vec = 0;

void inc_counter_vec() {
  IC_API ic_api(false);
  for (uint64_t i = 0; i < len_counter_vec; ++i) {
    p_counter_vec[i] += 1;
  }
}

void read_counter_vec() {
  IC_API ic_api(false);
  std::vector<uint64_t> counter_vec =
      ic_api.retrieve_vector_orthogonal(p_counter_vec, len_counter_vec);
  ic_api.to_wire(CandidTypeVecNat64{counter_vec});
}

void write_counter_vec() {
  IC_API ic_api(false);
  std::vector<uint64_t> counter_vec;
  ic_api.from_wire(CandidTypeVecNat64{&counter_vec});
  ic_api.store_vector_orthogonal(counter_vec, &p_counter_vec, &len_counter_vec);
}

// Calling a query function does NOT persist between calls. Try it out...
void inc_query_counter_vec() {
  IC_API ic_api(false);
  for (uint64_t i = 0; i < len_counter_vec; ++i) {
    p_counter_vec[i] += 1;
  }
}