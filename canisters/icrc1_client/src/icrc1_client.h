// file: src/icrc1_client.h
#pragma once
#include "wasm_symbol.h"
void token_info() WASM_SYMBOL_EXPORTED("canister_update token_info");
void balance() WASM_SYMBOL_EXPORTED("canister_update balance");
void transfer() WASM_SYMBOL_EXPORTED("canister_update transfer");
