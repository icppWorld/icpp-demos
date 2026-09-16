// file: src/demo_cycles.h
#pragma once
#include "wasm_symbol.h"
void demo_cycles_balances()
    WASM_SYMBOL_EXPORTED("canister_query demo_cycles_balances");
void demo_burn_cycles()
    WASM_SYMBOL_EXPORTED("canister_update demo_burn_cycles");
