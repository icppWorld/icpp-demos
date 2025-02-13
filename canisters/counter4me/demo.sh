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
echo "Building the wasm with wasi-sdk"
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
echo "Testing counter4me with dfx"

echo "- Check initial state of counter4me:"
dfx canister call --identity default counter4me  read_counter4me

echo "- Write the initial state for counter of default identity:"
dfx canister call --identity default counter4me write_counter4me '(10: nat64)'

echo "- Verify the state change of counter4me persists:"
dfx canister call --identity default counter4me read_counter4me

echo "- Increment counter for default identity, using an update call:"
dfx canister call --identity default counter4me inc_counter4me

echo "- Verify the state change of counter4me persists:"
dfx canister call --identity default counter4me read_counter4me

echo "- Write the initial state for counter of anonymous identity:"
dfx canister call --identity anonymous counter4me write_counter4me '(10: nat64)'

echo "- Verify the state change of counter4me persists:"
dfx canister call --identity anonymous counter4me read_counter4me

echo "- Increment counter for anonymous identity, using an update call:"
dfx canister call --identity anonymous counter4me inc_counter4me

echo "- Verify the state change of counter4me persists:"
dfx canister call --identity anonymous counter4me read_counter4me

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
echo "Building the OS native debug executable with clang++"
icpp build-native --to-compile all
# icpp build-native --to-compile mine

#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Running the OS native debug executable"
./build-native/mockic.exe