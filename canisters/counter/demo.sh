#!/bin/sh

echo "------------------------------------------"
echo "Starting a clean local network"
dfx stop
dfx start --clean --background

echo "------------------------------------------"
echo "Building & deploying the canister"
dfx deploy

echo "------------------------------------------"
echo "Running some tests with dfx"
dfx canister call counter read
dfx canister call counter inc
dfx canister call counter read
dfx canister call counter write '(10)'
dfx canister call counter read
dfx canister call counter inc_query
dfx canister call counter read

echo "------------------------------------------"
echo "Running the smoketests (requires icpp-pro)"
pytest --network=local