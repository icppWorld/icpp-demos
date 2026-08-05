"""Returns the icp-py-core Canister instance, for calling the endpoints."""

import json
import os
import sys
import subprocess
from pathlib import Path
from typing import Any, List, Optional
from icp_core import Agent, Identity, Client, Canister
from icpp.run_shell_cmd import run_shell_cmd

ROOT_PATH = Path(__file__).parent.parent

# We use icp-cli to get some information.
ICP = "icp"

# The identity to sign the calls with. It is the same one `demo.sh` deploys
# with, so these uploads/downloads run as the canister's controller. It is
# named explicitly: the machine-wide active identity (`icp identity default`)
# is never read, because any other process can change it at any moment.
TEST_IDENTITY = os.environ.get("ICPP_PRO_TEST_IDENTITY", "icpp-demos-testing")


def extract_variant(response: List[Any]) -> Any:
    """Extract variant result from icp-py-core response.

    icp-py-core returns: [{'type': 'variant', 'value': {'Ok': {...}}}]
    old ic-py returned:  [{'Ok': {...}}]
    This helper normalizes both formats to {'Ok': {...}} or {'Err': ...}.
    """
    item = response[0]
    if "value" in item:
        return item["value"]
    return item


def run_icp_command(cmd: str, quiet: bool = False) -> Optional[str]:
    """Runs an icp command as a subprocess.

    Runs from ROOT_PATH so icp finds this canister's `icp.yaml`, and closes
    stdin so icp can never block on an interactive prompt.
    """
    try:
        return run_shell_cmd(
            f"{cmd} < /dev/null", capture_output=True, cwd=ROOT_PATH
        ).rstrip("\n")
    except subprocess.CalledProcessError as e:
        if not quiet:
            print(f"Failed icp command: '{cmd}' with error: \n{e.output}")
    return None


def get_agent(network: str = "local") -> Agent:
    """Returns an icp-py-core Agent instance"""

    # Check if the network is up
    print(f"--\nChecking if the {network} network is up...")
    run_icp_command(f"{ICP} network ping --environment {network} ")
    print("Ok!")

    # Set the network URL.
    #
    # The local network runs on an ephemeral port (`gateway.port: 0` in
    # icp.yaml), so it MUST be read back - it differs on every
    # `icp network start`.
    status = run_icp_command(f"{ICP} network status --environment {network} --json ")
    if status is None:
        print(f"Error: could not get the status of the '{network}' network.")
        sys.exit(1)
    # `icp` reports it with a trailing slash, which must be stripped: icp-py-core
    # builds its endpoints as f"{url}/api/v2/...", so the slash would produce a
    # `//api/...` path that the gateway rejects with `canister_id_not_resolved`.
    network_url = json.loads(status)["api_url"].rstrip("/")

    print(f"Network URL        = {network_url}")

    print(f"Using identity = {TEST_IDENTITY}")

    # Get the private key of that identity, to sign the calls locally.
    # It must have been created with `--storage plaintext` to be exportable.
    private_key = run_icp_command(f"{ICP} identity export {TEST_IDENTITY} ")
    if private_key is None:
        print(
            f"Error: could not export the identity '{TEST_IDENTITY}'.\n"
            f"Create it, or point $ICPP_PRO_TEST_IDENTITY at another one:\n"
            f"    icp identity new {TEST_IDENTITY} --storage plaintext"
        )
        sys.exit(1)

    # Create an Identity instance using the private key
    identity = Identity.from_pem(private_key)

    # Create an HTTP client instance for making HTTPS calls to the IC
    # https://smartcontracts.org/docs/interface-spec/index.html#http-interface
    client = Client(url=network_url)

    # Create an IC agent to communicate with IC canisters
    agent = Agent(identity, client)
    return agent


def get_canister(
    canister_name: str,
    candid_path: Path,
    network: str = "local",
    canister_id: Optional[str] = "",
) -> Canister:
    """Returns an icp-py-core Canister instance"""

    agent = get_agent(network=network)

    # Try to get the id of the canister if not provided explicitly.
    # This reads icp's canister ID store, so it works without the network.
    # We also provide the option to just pass in the canister_id directly.
    if canister_id == "":
        canister_id = run_icp_command(
            f"{ICP} canister status {canister_name} "
            f"--environment {network} --id-only "
        )
    print(f"Canister ID = {canister_id}")

    # Read canister's candid from file
    with open(
        candid_path,
        "r",
        encoding="utf-8",
    ) as f:
        canister_did = f.read()

    # Create a Canister instance
    return Canister(agent=agent, canister_id=canister_id, candid_str=canister_did)
