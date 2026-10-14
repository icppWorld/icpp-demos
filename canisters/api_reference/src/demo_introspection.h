// file: src/demo_introspection.h
#pragma once
#include "wasm_symbol.h"
void demo_introspection()
    WASM_SYMBOL_EXPORTED("canister_update demo_introspection");
void demo_introspection_query()
    WASM_SYMBOL_EXPORTED("canister_query demo_introspection_query");
