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
echo "Testing counter with dfx"
dfx canister call counter read
dfx canister call counter inc
dfx canister call counter read
dfx canister call counter write '(10)'
dfx canister call counter read
dfx canister call counter inc_query
dfx canister call counter read

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