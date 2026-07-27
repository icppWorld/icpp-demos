#!/bin/sh

#######################################################################
# This is a Linux & Mac shell script
#
# (-) Install icpp-pro in a python environment
# (-) Install icp-cli: npm install -g @icp-sdk/icp-cli
# (-) In a terminal:
#
#     ./demo.sh
#
#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Stopping the local network"
icp network stop

echo " "
echo "--------------------------------------------------"
echo "Starting the local network as a background process"
# icp-cli has no `--clean` flag: a managed network keeps its state in
# .icp/cache (NOT .icp/data, which holds the mainnet canister ids)
rm -rf .icp/cache
icp network start --background

#######################################################################
echo "--------------------------------------------------"
echo "Building the wasm with icpp-pro"
icpp build-wasm --to-compile all
# icpp build-wasm --to-compile mine

#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Deploying the wasm to a canister on the local network"
icp deploy --environment local --yes

#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Testing counters with icp"

echo "- Check initial state of counters:"
icp canister call counters read_counters '()' --environment local

echo "- Write the initial state of 2 counters:"
icp canister call counters write_counters '(vec { 10 : nat64; 10 : nat64 })' --environment local

echo "- Verify the state change of counters persists:"
icp canister call counters read_counters '()' --environment local

echo "- Increment the 2 counters, using an update call:"
icp canister call counters inc_counters '()' --environment local

echo "- Verify the state change of counters persists:"
icp canister call counters read_counters '()' --environment local

echo "- Add two more counters:"
icp canister call counters additional_counters '(vec { 10 : nat64; 10 : nat64 })' --environment local

echo "- Verify the state change of counters persists:"
icp canister call counters read_counters '()' --environment local

echo "- Increment the 4 counters, using an update call:"
icp canister call counters inc_counters '()' --environment local

echo "- Verify the state change of counters persists:"
icp canister call counters read_counters '()' --environment local

#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Running the full smoketests with pytest"
pytest --network=local

#######################################################################
echo "--------------------------------------------------"
echo "Stopping the local network"
icp network stop

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