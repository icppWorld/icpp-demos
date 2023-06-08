#pragma once

#include "wasm_symbol.h"

void inc_counter_for_caller()
    WASM_SYMBOL_EXPORTED("canister_update inc_counter_for_caller");
void read_counter_for_caller()
    WASM_SYMBOL_EXPORTED("canister_query read_counter_for_caller");
void write_counter_for_caller()
    WASM_SYMBOL_EXPORTED("canister_update write_counter_for_caller");
void inc_query_counter_for_caller()
    WASM_SYMBOL_EXPORTED("canister_query inc_query_counter_for_caller");
