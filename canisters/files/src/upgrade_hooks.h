#pragma once

#include "wasm_symbol.h"

// docs start: upgrade_hooks_h
void canister_pre_upgrade() WASM_SYMBOL_EXPORTED("canister_pre_upgrade");
void canister_post_upgrade() WASM_SYMBOL_EXPORTED("canister_post_upgrade");
// docs end: upgrade_hooks_h

void upgrade_history() WASM_SYMBOL_EXPORTED("canister_query upgrade_history");
