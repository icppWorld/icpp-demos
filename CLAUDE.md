# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with
code in this repository.

## Project Overview

icpp-demos holds the example C++ smart contracts for
[icpp-pro](https://docs.icpp.world). Every subfolder of `canisters/` is a
standalone icpp-pro project (`icpp.toml` + `icp.yaml` + `src/` + `native/` +
`test/` + `demo.sh`): `api_reference`, `counter`, `counter4me`, `counters`,
`files`, `memory`.

This repo is part of the icpp-pro repo family. The feature-development and
release process lives in `../icpp-pro/README-feature-guide.md` — follow it
when a change here relates to an icpp-pro feature or release.

## Role in the repo family

- **Depends on icpp-pro from PyPI**: `requirements.txt` pins
  `icpp-pro>=X.Y.Z` (bumped every icpp-pro release) plus black/pylint/mypy at
  the same versions as icpp-pro. `../icpp-pro`'s `make check-sibling-pins`
  verifies the pins.
- **Feeds the docs**: `../icpp-docs` `{%include%}`s files from this repo by
  relative path — especially `canisters/api_reference/src/`, whose demo
  functions appear verbatim in the API reference. Renaming or moving them
  breaks the docs build (`make -C ../icpp-docs mkdocs-build` to check).
- **Verification target**: `make all-tests` here is the "demos" leg of
  icpp-pro's `make siblings-verify-api` / `siblings-verify-full`.
- The `files` canister is the default subject of icpp-pro's
  `make upgrade-test`: its tests write files and re-verify them after a
  canister upgrade via the `run_after_upgrade` pytest marker.

## Common Commands

| Command                                          | Purpose                                        |
|--------------------------------------------------|------------------------------------------------|
| `make all-tests`                                 | Everything: static checks + native + deploy + pytest |
| `make all-static`                                | clang-format + black + pylint + mypy           |
| `make all-canister-native`                       | Build & run every canister's Mock IC executable |
| `make all-canister-deploy-local-pytest`          | Build wasm, deploy to local networks, pytest   |
| `make all-canister-deploy-local-pytest JOBS=1`   | Same, serial, with live output (debugging)     |

Python environment: the icpp-pro dev env with demos extras —
`make -C ../icpp-pro install-python-w-demos` (see
`../icpp-pro/README-contributors-guide.md`).

## Testing identity

Tests deploy and run as the explicit identity `icpp-demos-testing`
(`ICPP_PRO_TEST_IDENTITY`), auto-created by the Makefile. The machine-wide
active identity (`icp identity default`) is never read or written.
