#pragma once

#include "wasm_symbol.h"

void canister_init() WASM_SYMBOL_EXPORTED("canister_init");
void write_counters() WASM_SYMBOL_EXPORTED("canister_update write_counters");
void additional_counters()
    WASM_SYMBOL_EXPORTED("canister_update additional_counters");
void inc_counters() WASM_SYMBOL_EXPORTED("canister_update inc_counters");
void read_counters() WASM_SYMBOL_EXPORTED("canister_query read_counters");