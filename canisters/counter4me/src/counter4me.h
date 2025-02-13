#pragma once

#include "wasm_symbol.h"

void write_counter4me()
    WASM_SYMBOL_EXPORTED("canister_update write_counter4me");
void inc_counter4me() WASM_SYMBOL_EXPORTED("canister_update inc_counter4me");
void read_counter4me() WASM_SYMBOL_EXPORTED("canister_query read_counter4me");