// file: src/demo_certified_data.h
#pragma once
#include "wasm_symbol.h"
void demo_certified_data_set()
    WASM_SYMBOL_EXPORTED("canister_update demo_certified_data_set");
void demo_get_data_certificate()
    WASM_SYMBOL_EXPORTED("canister_query demo_get_data_certificate");
