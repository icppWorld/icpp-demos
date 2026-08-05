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
#######################################################################
# The identity we deploy with and run the tests as. It is named explicitly and
# passed to every icp command, so the machine-wide active identity
# (`icp identity default`) is never read and never changed - running this demo
# cannot disturb the identity you use for mainnet work.
ICPP_PRO_TEST_IDENTITY=${ICPP_PRO_TEST_IDENTITY:-icpp-demos-testing}
export ICPP_PRO_TEST_IDENTITY
# `icp identity principal` exits non-zero for an unknown name, which is an exact
# check - unlike grepping `icp identity list`.
icp identity principal --identity "$ICPP_PRO_TEST_IDENTITY" >/dev/null 2>&1 || \
  icp identity new "$ICPP_PRO_TEST_IDENTITY" --storage plaintext

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
icp deploy --environment local --yes --identity "$ICPP_PRO_TEST_IDENTITY"

#######################################################################
echo " "
echo "--------------------------------------------------"
echo "Testing counter with icp"
icp canister call counter read '()' --environment local --identity "$ICPP_PRO_TEST_IDENTITY"
icp canister call counter inc '()' --environment local --identity "$ICPP_PRO_TEST_IDENTITY"
icp canister call counter read '()' --environment local --identity "$ICPP_PRO_TEST_IDENTITY"
icp canister call counter write '(10)' --environment local --identity "$ICPP_PRO_TEST_IDENTITY"
icp canister call counter read '()' --environment local --identity "$ICPP_PRO_TEST_IDENTITY"
icp canister call counter inc_query '()' --environment local --identity "$ICPP_PRO_TEST_IDENTITY"
icp canister call counter read '()' --environment local --identity "$ICPP_PRO_TEST_IDENTITY"

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