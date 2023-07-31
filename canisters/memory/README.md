# Orthogonal Persistence of C++ Data Structures on the Internet Computer: A Study

I've been experimenting with orthogonal persistence of various C++ data structures in canisters on the Internet Computer (IC) and would like to share my findings with the community.

## Here are the key points:

1. Data structures fully living in the global/static section of the stack are correctly persisted. This includes regular data types like `int`, `float`, `uint64_t`, etc. and the special STL container `std::array`, which keeps all its data on the stack.
2. Self-managed dynamic data structures are correctly persisted too. This is when the data lives on the Heap, but the pointer to the data is in the global/static section of the stack. This was tested for both `new/delete` and `calloc/free` style memory management.
3. Self-managed pointers to STL containers like std::vector also work. As long as you self manage a pointer in the global/static memory, and then use new/delete on them inside your functions.
4. Defining STL containers like std::vector directly in global/static section is not working. Not only are they not persisted, just adding these to the global/static section corrupts the canister memory, even if you’re not using them at all… The tests show that the metadata for the std::vector (like its size and the Heap address pointed to by the vector) is persisted, but the actual values aren’t.

## To replicate the experiment

The code for testing std::vector defined directly in global/static section has been outcommented. If you want to test that, please edit the file `src/memory.cpp` first and uncomment the relevant lines.

To run the experiment, follow these instructions. 

 - We assume you already have dfx installed
   - On Windows, dfx runs in wsl, but you will issue these commands in a PowerShell/Miniconda shell, and simply prefix the dfx commands with: `wsl --% dfx ...`

- [Install](https://docs.icpp.world/installation.html):  
  ```bash
  pip install icpp-pro
  icpp install-wasi-sdk # installs wasi-sdk compiler in ~/.icpp
  ```
- Start the local network:
  ```bash
  dfx start --clean
  ```
- Then run these commands:
  ```bash
  icpp build-wasm  # second time, add this option: --to-compile mine
  dfx deploy
  dfx canister call memory change_memory # see debug_print of canister
  dfx canister call memory print_memory  # see debug_print of canister
  ```

The debug_print in the canister shows the following:

```bash
dfx canister call memory change_memory
[Canister ...-cai] ------
[Canister ...-cai] change_memory:
[Canister ...-cai]  
[Canister ...-cai] i1 = 0
[Canister ...-cai]  
[Canister ...-cai] arr1.size() = 2
[Canister ...-cai] arr1[0] = 0
[Canister ...-cai] arr1[1] = 0
[Canister ...-cai] arr1.data() address = 0x14820
[Canister ...-cai]  
[Canister ...-cai] p_nd_i1[0] = 0
[Canister ...-cai] p_nd_i1[1] = 0
[Canister ...-cai] p_nd_i1 address = 0x148b0
[Canister ...-cai]  
[Canister ...-cai] p_cf_i1[0] = 0
[Canister ...-cai] p_cf_i1[1] = 0
[Canister ...-cai] p_cf_i1 address = 0x14a90
[Canister ...-cai]  
[Canister ...-cai] (*p_vec1).size() = 2
[Canister ...-cai] (*p_vec1)[0] = 0
[Canister ...-cai] (*p_vec1)[1] = 0
[Canister ...-cai] (*p_vec1).data() address = 0x14ac0
[Canister ...-cai]  
[Canister ...-cai] p_vec2->vec.size() = 2
[Canister ...-cai] p_vec2->vec[0] = 0
[Canister ...-cai] p_vec2->vec[1] = 0
[Canister ...-cai] p_vec2->vec.data() address = 0x14af0
[Canister ...-cai]  
[Canister ...-cai] vec1.size() = 2
[Canister ...-cai] vec1[0] = 0
[Canister ...-cai] vec1[1] = 0
[Canister ...-cai] vec1.data() address = 0x14870
[Canister ...-cai]  
[Canister ...-cai] vec101.vec.size() = 2
[Canister ...-cai] vec101.vec[0] = 0
[Canister ...-cai] vec101.vec[1] = 0
[Canister ...-cai] vec101.vec.data() address = 0x14890
[Canister ...-cai] ------
[Canister ...-cai] change_memory:
[Canister ...-cai]  
[Canister ...-cai] i1 = 1
[Canister ...-cai]  
[Canister ...-cai] arr1.size() = 2
[Canister ...-cai] arr1[0] = 1
[Canister ...-cai] arr1[1] = 1
[Canister ...-cai] arr1.data() address = 0x14820
[Canister ...-cai]  
[Canister ...-cai] p_nd_i1[0] = 1
[Canister ...-cai] p_nd_i1[1] = 1
[Canister ...-cai] p_nd_i1 address = 0x148b0
[Canister ...-cai]  
[Canister ...-cai] p_cf_i1[0] = 1
[Canister ...-cai] p_cf_i1[1] = 1
[Canister ...-cai] p_cf_i1 address = 0x14a90
[Canister ...-cai]  
[Canister ...-cai] (*p_vec1).size() = 2
[Canister ...-cai] (*p_vec1)[0] = 1
[Canister ...-cai] (*p_vec1)[1] = 1
[Canister ...-cai] (*p_vec1).data() address = 0x14ac0
[Canister ...-cai]  
[Canister ...-cai] p_vec2->vec.size() = 2
[Canister ...-cai] p_vec2->vec[0] = 1
[Canister ...-cai] p_vec2->vec[1] = 1
[Canister ...-cai] p_vec2->vec.data() address = 0x14af0
[Canister ...-cai]  
[Canister ...-cai] vec1.size() = 2
[Canister ...-cai] vec1[0] = 1
[Canister ...-cai] vec1[1] = 1
[Canister ...-cai] vec1.data() address = 0x14870
[Canister ...-cai]  
[Canister ...-cai] vec101.vec.size() = 2
[Canister ...-cai] vec101.vec[0] = 1
[Canister ...-cai] vec101.vec[1] = 1
[Canister ...-cai] vec101.vec.data() address = 0x14890
```

```bash
dfx canister call memory print_memory
[Canister ...-cai] ------
[Canister ...-cai] print_memory:
[Canister ...-cai]  
[Canister ...-cai] i1 = 1
[Canister ...-cai]  
[Canister ...-cai] arr1.size() = 2
[Canister ...-cai] arr1[0] = 1
[Canister ...-cai] arr1[1] = 1
[Canister ...-cai] arr1.data() address = 0x14820
[Canister ...-cai]  
[Canister ...-cai] p_nd_i1[0] = 1
[Canister ...-cai] p_nd_i1[1] = 1
[Canister ...-cai] p_nd_i1 address = 0x148b0
[Canister ...-cai]  
[Canister ...-cai] p_cf_i1[0] = 1
[Canister ...-cai] p_cf_i1[1] = 1
[Canister ...-cai] p_cf_i1 address = 0x14a90
[Canister ...-cai]  
[Canister ...-cai] (*p_vec1).size() = 2
[Canister ...-cai] (*p_vec1)[0] = 1
[Canister ...-cai] (*p_vec1)[1] = 1
[Canister ...-cai] (*p_vec1).data() address = 0x14ac0
[Canister ...-cai]  
[Canister ...-cai] p_vec2->vec.size() = 2
[Canister ...-cai] p_vec2->vec[0] = 1
[Canister ...-cai] p_vec2->vec[1] = 1
[Canister ...-cai] p_vec2->vec.data() address = 0x14af0
[Canister ...-cai]  
[Canister ...-cai] vec1.size() = 2
[Canister ...-cai] vec1[0] = 0                              # NOT OK!
[Canister ...-cai] vec1[1] = 0                              # NOT OK!
[Canister ...-cai] vec1.data() address = 0x14870
[Canister ...-cai]  
[Canister ...-cai] vec101.vec.size() = 2
[Canister ...-cai] vec101.vec[0] = 0                        # NOT OK!
[Canister ...-cai] vec101.vec[1] = 0                        # NOT OK!
[Canister ...-cai] vec101.vec.data() address = 0x14890
```