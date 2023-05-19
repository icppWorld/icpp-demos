[![icpp-demos](https://github.com/icppWorld/icpp-demos/actions/workflows/cicd.yml/badge.svg)](https://github.com/icppWorld/icpp-demos/actions/workflows/cicd.yml)

# icpp-demos

Example C++ Smart Contracts that you can deploy to the Internet Computer with [icpp-pro](https://docs.icpp.world).

## The Smart Contracts

Each sub folder of `canisters` is a standalone icpp-pro development project.

| canister      | content                                                      |
| ------------- | ------------------------------------------------------------ |
| api_reference | The [api-reference docs](https://docs.icpp.world/api-reference.html) example code. |

## Setup

Follow the [icpp-pro installation](https://docs.icpp.world/installation.html) instructions

## Deploy & Manually test

```bash
# Goto root folder of a canister, eg.
cd canisters/api_reference

# Start the local network
dfx start --clean --background

# Deploy the canister
dfx deploy

# Manually test the canister methods, eg.
$ dfx canister call --type idl --output idl demo demo_get_caller '()'
Hello! Your principal is expmt-gtxsw-inftj-ttabj-qhp5s-nozup-n3bbo-k7zvn-dg4he-knac3-lae

```

## Smoketest

```bash
# Smoketest the deployed canister
pytest --network local

# or, after deploying to mainnet
pytest --network ic
```



## Native debug

```bash
# Build native debug executable with MockIC
icpp build-native

# Run it directly, or debug it in VS Code
build-native/mockic.exe 
```



