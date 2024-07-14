#pragma once

#include "wasm_symbol.h"

void write_read_during_query()
    WASM_SYMBOL_EXPORTED("canister_query write_read_during_query");
void write_read_during_update()
    WASM_SYMBOL_EXPORTED("canister_update write_read_during_update");