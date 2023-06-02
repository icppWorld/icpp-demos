#pragma once

#include "wasm_symbol.h"

void inc_counter_vec() WASM_SYMBOL_EXPORTED("canister_update inc_counter_vec");
void read_counter_vec() WASM_SYMBOL_EXPORTED("canister_query read_counter_vec");
void write_counter_vec()
    WASM_SYMBOL_EXPORTED("canister_update write_counter_vec");
void inc_query_counter_vec()
    WASM_SYMBOL_EXPORTED("canister_query inc_query_counter_vec");