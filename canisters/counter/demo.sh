#!/bin/sh

echo "------------------------------------------"
echo "Starting a clean local network"
dfx stop
dfx start --clean --background

echo "------------------------------------------"
echo "Building & deploying the canister"
dfx deploy

echo "------------------------------------------"
echo "Testing counter with dfx"
dfx canister call counter read
dfx canister call counter inc
dfx canister call counter read
dfx canister call counter write '(10)'
dfx canister call counter read
dfx canister call counter inc_query
dfx canister call counter read

echo "------------------------------------------"
echo "Testing counter_vec with dfx"
dfx canister call counter read_counter_vec
dfx canister call counter write_counter_vec '(vec { 10 : nat64; 10 : nat64 })'
dfx canister call counter read_counter_vec
dfx canister call counter inc_query_counter_vec
dfx canister call counter read_counter_vec

echo "------------------------------------------"
echo "Running the smoketests (requires icpp-pro)"
pytest --network=local