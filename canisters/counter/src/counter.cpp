// Demo of a counter, stored in static memory

#include "counter.h"
#include "ic_api.h"

// State of the Smart Contract, using Orthogonal Persistence
// For Orthogonal Persistence to work, the data must be managed at a global level
uint64_t counter{0};

void inc() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  counter += 1;
}

void read() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  ic_api.to_wire(CandidTypeNat64{counter});
}

void write() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  ic_api.from_wire(CandidTypeNat64{&counter});
}

// Calling a query function does NOT persist between calls. Try it out...
void inc_query() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  counter += 1;
}