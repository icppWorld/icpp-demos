# Orthogonal Persistence of C++ Data Structures on the Internet Computer: A Study

I've been experimenting with orthogonal persistence of various C++ data structures in canisters on the Internet Computer (IC) and would like to share my findings with the community.

This canister is NOT deployed to the IC, because the investigation relies on print statements, which only work in the local network.

## Here are the key points:

Since icpp-pro 4.1.0, all data structures defined in the static section of your C++ code will be correctly persisted.

## To replicate the experiment

To run the experiment, follow these instructions. 

 - We assume you already have icp-cli installed

- [Install](https://docs.icpp.world/installation.html):  
  ```bash
  pip install icpp-pro
  ```
- Start the local network:
  ```bash
  icp network stop
  rm -rf .icp/cache
  icp network start --background
  ```
- Then run these commands:
  ```bash
  icpp build-wasm  # second time, add this option: --to-compile mine-no-lib
  icp deploy --environment local --yes
  icp canister call memory change_memory '()' --environment local # see output in the local network log
  icp canister call memory print_memory '()' --environment local  # see output in the local network log
  ```