#pragma once

#include "wasm_symbol.h"

void change_memory() WASM_SYMBOL_EXPORTED("canister_update change_memory");
void print_memory() WASM_SYMBOL_EXPORTED("canister_query print_memory");
