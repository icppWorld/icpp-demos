#!/bin/sh

#######################################################################
# This is a Linux & Mac shell script
#
# (-) Install icpp-pro in a python environment
# (-) Install dfx
# (-) In a terminal:
#
#     ./demo.sh
#
#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Stopping the local network"
dfx stop

echo " "
echo "--------------------------------------------------"
echo "Starting the local network as a background process"
dfx start --clean --background

#######################################################################
echo "--------------------------------------------------"
echo "Building the wasm with icpp-pro"
icpp build-wasm --to-compile all
# icpp build-wasm --to-compile mine

#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Deploying the wasm to a canister on the local network"
dfx deploy

#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Testing counters with dfx"

echo "- Check initial state of counters:"
dfx canister call counters read_counters

echo "- Write the initial state of 2 counters:"
dfx canister call counters write_counters '(vec { 10 : nat64; 10 : nat64 })'

echo "- Verify the state change of counters persists:"
dfx canister call counters read_counters

echo "- Increment the 2 counters, using an update call:"
dfx canister call counters inc_counters

echo "- Verify the state change of counters persists:"
dfx canister call counters read_counters

echo "- Add two more counters:"
dfx canister call counters additional_counters '(vec { 10 : nat64; 10 : nat64 })'

echo "- Verify the state change of counters persists:"
dfx canister call counters read_counters

echo "- Increment the 4 counters, using an update call:"
dfx canister call counters inc_counters

echo "- Verify the state change of counters persists:"
dfx canister call counters read_counters

#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Running the full smoketests with pytest"
pytest --network=local

#######################################################################
echo "--------------------------------------------------"
echo "Stopping the local network"
dfx stop

#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Building the OS native debug executable with icpp-pro"
icpp build-native --to-compile all
# icpp build-native --to-compile mine

#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Running the OS native debug executable"
./build-native/mockic.exe