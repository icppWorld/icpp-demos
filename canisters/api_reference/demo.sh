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
dfx canister call demo demo_candid_type_bool '(true)'
dfx canister call demo demo_candid_type_bools '(true, false)'
# ...etc...

echo "------------------------------------------"
echo "Running the smoketests (requires icpp-pro)"
pytest --network=local