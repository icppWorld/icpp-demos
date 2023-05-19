// file: src/demo_to_wire.h
#pragma once
#include "wasm_symbol.h"
void demo_to_wire_no_arg()
    WASM_SYMBOL_EXPORTED("canister_query demo_to_wire_no_arg");
void demo_to_wire_one_arg()
    WASM_SYMBOL_EXPORTED("canister_query demo_to_wire_one_arg");
void demo_to_wire_multiple_args()
    WASM_SYMBOL_EXPORTED("canister_query demo_to_wire_multiple_args");