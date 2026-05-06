/* file: src/demo_timers.cpp

Demo of the icpp-pro multi-timer API:
  IC_API::set_timer(delay_ns, cb)            // one-shot, returns timer id
  IC_API::set_timer_recurring(period_ns, cb) // recurring, returns timer id
  IC_API::cancel_timer(id)                   // cancel one, returns bool
  IC_API::cancel_all_timers()                // cancel all + disarm

The IC platform exposes a single global timer per canister; icpp-pro layers
a multi-timer scheduler on top and auto-exports a `canister_global_timer`
dispatcher (marked weak so users can override it). Timer state is in-memory
only — re-register your timers in `canister_post_upgrade` if needed.

Example session:

  $ dfx canister call --type idl --output idl demo demo_set_timer '(0 : nat64)'
  (1 : nat64)

  # ... wait ~1s for the IC to fire canister_global_timer ...

  $ dfx canister call --type idl --output idl demo demo_get_one_shot_fires '()'
  (1 : nat64)

  $ dfx canister call --type idl --output idl demo demo_set_timer_recurring '(1_000_000_000 : nat64)'
  (2 : nat64)

  # ... wait a few seconds ...

  $ dfx canister call --type idl --output idl demo demo_get_recurring_fires '()'
  (3 : nat64)

  $ dfx canister call --type idl --output idl demo demo_cancel_timer '(2 : nat64)'
  (true)

  $ dfx canister call --type idl --output idl demo demo_cancel_all_timers '()'
  ()

*/
#include "demo_timers.h"
#include "ic_api.h"

namespace {
// Counters exposed via the demo_get_*_fires query methods. The lambdas
// passed to set_timer / set_timer_recurring capture references to these
// (or, since they're file-scope statics, just reference them directly).
uint64_t g_one_shot_fires{0};
uint64_t g_recurring_fires{0};
} // namespace

void demo_set_timer() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  uint64_t delay_ns{0};
  ic_api.from_wire(CandidTypeNat64{&delay_ns});

  uint64_t id = IC_API::set_timer(delay_ns, []() { ++g_one_shot_fires; });

  ic_api.to_wire(CandidTypeNat64{id});
}

void demo_set_timer_recurring() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  uint64_t period_ns{0};
  ic_api.from_wire(CandidTypeNat64{&period_ns});

  uint64_t id =
      IC_API::set_timer_recurring(period_ns, []() { ++g_recurring_fires; });

  ic_api.to_wire(CandidTypeNat64{id});
}

void demo_cancel_timer() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  uint64_t id{0};
  ic_api.from_wire(CandidTypeNat64{&id});

  bool ok = IC_API::cancel_timer(id);

  ic_api.to_wire(CandidTypeBool{ok});
}

void demo_cancel_all_timers() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  ic_api.from_wire();

  IC_API::cancel_all_timers();

  ic_api.to_wire();
}

void demo_get_one_shot_fires() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  ic_api.from_wire();
  ic_api.to_wire(CandidTypeNat64{g_one_shot_fires});
}

void demo_get_recurring_fires() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  ic_api.from_wire();
  ic_api.to_wire(CandidTypeNat64{g_recurring_fires});
}

void demo_reset_timer_counters() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  ic_api.from_wire();

  g_one_shot_fires = 0;
  g_recurring_fires = 0;
  IC_API::cancel_all_timers();

  ic_api.to_wire();
}
