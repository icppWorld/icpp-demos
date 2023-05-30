#pragma once

#include "wasm_symbol.h"

void inc() WASM_SYMBOL_EXPORTED("canister_update inc");
void read() WASM_SYMBOL_EXPORTED("canister_query read");
void write() WASM_SYMBOL_EXPORTED("canister_update write");
void inc_query() WASM_SYMBOL_EXPORTED("canister_query inc_query");