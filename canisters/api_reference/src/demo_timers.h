// file: src/demo_timers.h
#pragma once
#include "wasm_symbol.h"

// Schedule a one-shot callback to fire after `delay_ns` nanoseconds.
// Returns the timer id (a non-zero nat64) you can later pass to cancel.
void demo_set_timer() WASM_SYMBOL_EXPORTED("canister_update demo_set_timer");

// Schedule a recurring callback to fire every `period_ns` nanoseconds.
// Returns the timer id.
void demo_set_timer_recurring()
    WASM_SYMBOL_EXPORTED("canister_update demo_set_timer_recurring");

// Cancel a previously registered timer by id. Returns true if the id was
// found and removed, false if it was unknown.
void demo_cancel_timer()
    WASM_SYMBOL_EXPORTED("canister_update demo_cancel_timer");

// Cancel every currently registered timer (one-shot and recurring) and
// disarm the IC's global timer.
void demo_cancel_all_timers()
    WASM_SYMBOL_EXPORTED("canister_update demo_cancel_all_timers");

// Query how many times the one-shot callback has fired so far.
void demo_get_one_shot_fires()
    WASM_SYMBOL_EXPORTED("canister_query demo_get_one_shot_fires");

// Query how many times the recurring callback has fired so far.
void demo_get_recurring_fires()
    WASM_SYMBOL_EXPORTED("canister_query demo_get_recurring_fires");

// Reset both counters and cancel all timers — keeps the demo re-runnable
// without redeploying the canister.
void demo_reset_timer_counters()
    WASM_SYMBOL_EXPORTED("canister_update demo_reset_timer_counters");
