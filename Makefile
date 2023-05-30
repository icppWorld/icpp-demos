SHELL := /bin/bash

# Disable built-in rules and variables
MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

NETWORK := local

###########################################################################
# OS we're running on
ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Darwin)	  # Mac OS X  (Intel)
	OS += macos
	DIDC += didc-macos
endif
ifeq ($(detected_OS),Linux)		  # Ubuntu
	OS += linux
	DIDC += didc-linux64 
endif

ifeq ($(detected_OS),Windows_NT)  # Windows (icpp supports it but you cannot run this Makefile)
	OS += windows_cannot_run_make
endif
ifeq ($(detected_OS),Unknown)     # Unknown
	OS += unknown
endif

###########################################################################
# latest release of didc
VERSION_DIDC := $(shell curl --silent "https://api.github.com/repos/dfinity/candid/releases/latest" | grep -e '"tag_name"' | cut -c 16-25)
# version to install for clang
VERSION_CLANG := $(shell cat version_clang.txt)

###########################################################################
# Use some clang tools that come with wasi-sdk
ICPP_COMPILER_ROOT := $(HOME)/.icpp/wasi-sdk-16.0
CLANG_FORMAT = $(ICPP_COMPILER_ROOT)/bin/clang-format
CLANG_TIDY = $(ICPP_COMPILER_ROOT)/bin/clang-tidy

###########################################################################
# CI/CD - Phony Makefile targets
#
.PHONY: all-tests
all-tests: all-static all-canister-native all-canister-deploy-local-pytest 
	
.PHONY: all-canister-deploy-local-pytest
all-canister-deploy-local-pytest:
	dfx identity use default
	@python -m scripts.all_canister_deploy_local_pytest

.PHONY: all-canister-native
all-canister-native:
	@python -m scripts.all_canister_native

.PHONY: all-static
all-static: \
	cpp-format cpp-lint \
	python-format python-lint python-type
	
CPP_AND_H_FILES = $(shell ls \
canisters/*/src/*.cpp canisters/*/src/*.h)

.PHONY: cpp-format
cpp-format:
	@echo "---"
	@echo "cpp-format"
	$(CLANG_FORMAT) --style=file --verbose -i $(CPP_AND_H_FILES)

.PHONY: cpp-lint
cpp-lint:
	@echo "---"
	@echo "cpp-lint"
	@echo "TO IMPLEMENT with clang-tidy"

.PHONY: clean-dfx
clean-dfx:
	rm -rf $(shell find . -name '.dfx' -type d)

.PHONY: clean-build
clean-build:
	rm -rf build build-native build-native-unit
	rm -rf $(shell find ./src -name 'build' -type d)
	rm -rf $(shell find ./tests -name 'build' -type d)
	
.PHONY: python-clean
python-clean:
	find . -name '*.pyc' -exec rm -f {} +
	find . -name '*.pyo' -exec rm -f {} +
	find . -name '*~' -exec rm -f  {} +

PYTHON_DIRS ?= scripts canisters

.PHONY: python-format
python-format:
	@echo "---"
	@echo "python-format"
	python -m black $(PYTHON_DIRS)

.PHONY: python-lint
python-lint:
	@echo "---"
	@echo "python-lint"
	python -m pylint --jobs=0 --rcfile=.pylintrc $(PYTHON_DIRS)

.PHONY: python-type
python-type:
	@echo "---"
	@echo "python-type"
	python -m mypy --config-file .mypy.ini --show-column-numbers --strict --explicit-package-bases $(PYTHON_DIRS)


###########################################################################
# Toolchain installation for .github/workflows

.PHONY: install-clang-ubuntu
install-clang-ubuntu:
	@echo "Installing clang-$(VERSION_CLANG) compiler"
	sudo apt update && sudo apt install clang-$(VERSION_CLANG)

	@echo "Creating soft links for compiler executables"
	sudo ln --force -s /usr/bin/clang-$(VERSION_CLANG) /usr/bin/clang
	sudo ln --force -s /usr/bin/clang++-$(VERSION_CLANG) /usr/bin/clang++


# This installs ~/bin/dfx
# Make sure to source ~/.profile afterwards -> it adds ~/bin to the path if it exists
.PHONY: install-dfx
install-dfx:
	sh -ci "$$(curl -fsSL https://sdk.dfinity.org/install.sh)"

.PHONY: install-didc
install-didc:
	@echo "Installing didc $(VERSION_DIDC) ..."
	sudo rm -rf /usr/local/bin/didc
	wget https://github.com/dfinity/candid/releases/download/${VERSION_DIDC}/$(DIDC)
	sudo mv $(DIDC) /usr/local/bin/didc
	chmod +x /usr/local/bin/didc
	@echo " "
	@echo "Installed successfully in:"
	@echo /usr/local/bin/didc

.PHONY: install-jp
install-jp:
	sudo apt-get update && sudo apt-get install jp

.PHONY: install-python
install-python:
	pip install --upgrade pip
	pip install -e .[dev]

.PHONY:install-rust
install-rust:
	@echo "Installing rust"
	curl https://sh.rustup.rs -sSf | sh -s -- -y
	@echo "Installing ic-cdk-optimizer"
	cargo install ic-cdk-optimizer

.PHONY: install-wabt
install-wabt:
	sudo apt update && sudo apt install wabt
