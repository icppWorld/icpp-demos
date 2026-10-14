// file: src/demo_calls.h
#pragma once
#include "wasm_symbol.h"
void demo_call() WASM_SYMBOL_EXPORTED("canister_update demo_call");
void demo_call_callee()
    WASM_SYMBOL_EXPORTED("canister_update demo_call_callee");
void demo_yield() WASM_SYMBOL_EXPORTED("canister_update demo_yield");
