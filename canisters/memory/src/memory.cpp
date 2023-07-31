// Exploration of orthogonal persistence for various C++ data structures

#include "memory.h"
#include "ic_api.h"

#include <vector>

// -----------------------------------------------------------------------
// State of the Smart Contract, using Orthogonal Persistence
// For Orthogonal Persistence to work, the data must be managed at a global level

// --
// These work. Values are persisted after an update call.

// Fixed data structures with all data living on the stack
uint64_t i1{0};
std::array<uint64_t, 2> arr1{};

// Self managed dynamic data structures:
// (-) Memory lives on the Heap
// (-) Point to memory lives on the Stack in static/global section
// new & delete
uint64_t *p_nd_i1{nullptr};
// calloc & free  (C style)
uint64_t *p_cf_i1{nullptr};

// Self managed pointers to STL containters or wrapped STL containers
std::vector<uint64_t> *p_vec1{nullptr};

class MyVec {
public:
  MyVec() : vec{0, 0} {}
  std::vector<uint64_t> vec;
};
MyVec *p_vec2{nullptr};

// --
// These do NOT work.
// -> Values are not persisted after an update call.
// -> Just adding them here corrupts memory of the canister.
// Outcomment if you want to test
// std::vector<uint64_t> vec1(2, 0);
// MyVec vec101;

// -----------------------------------------------------------------------
// Helper functions
void new_memory() {
  p_nd_i1 = new (std::nothrow) uint64_t[2]();
  if (p_nd_i1 == nullptr) {
    IC_API::trap("Allocation of p_nd_i1 failed");
  }
  p_cf_i1 = static_cast<uint64_t *>(std::calloc(2, sizeof(uint64_t)));
  if (p_cf_i1 == nullptr) {
    IC_API::trap("Allocation of p_cf_i1 failed");
  }
  p_vec1 = new (std::nothrow) std::vector<uint64_t>(2, 0);
  if (p_vec1 == nullptr) {
    IC_API::trap("Allocation of p_vec1 failed");
  }
  p_vec2 = new (std::nothrow) MyVec();
  if (p_vec2 == nullptr) {
    IC_API::trap("Allocation of p_vec2 failed");
  }
}

void delete_memory() {
  if (p_nd_i1) {
    delete[] p_nd_i1;
    p_nd_i1 = nullptr;
  }
  if (p_cf_i1) {
    free(p_cf_i1);
    p_cf_i1 = nullptr;
  }
  if (p_vec1) {
    delete p_vec1;
    p_vec1 = nullptr;
  }
  if (p_vec2) {
    delete p_vec2;
    p_vec2 = nullptr;
  }
}

void change_it() {
  ++i1;

  ++arr1[0];
  ++arr1[1];

  ++p_nd_i1[0];
  ++p_nd_i1[1];

  ++p_cf_i1[0];
  ++p_cf_i1[1];

  ++(*p_vec1)[0];
  ++(*p_vec1)[1];

  ++p_vec2->vec[0];
  ++p_vec2->vec[1];

  // Outcomment if you want to test
  // ++vec1[0];
  // ++vec1[1];

  // ++vec101.vec[0];
  // ++vec101.vec[1];
}

void print_it(std::string caller) {
  char buffer[200]; // Make sure the buffer is large enough
  std::string pointer_string;

  IC_API::debug_print("------");
  IC_API::debug_print(caller + ":");

  IC_API::debug_print(" ");
  IC_API::debug_print("i1 = " + std::to_string(i1));

  IC_API::debug_print(" ");
  IC_API::debug_print("arr1.size() = " + std::to_string(arr1.size()));
  IC_API::debug_print("arr1[0] = " + std::to_string(arr1[0]));
  IC_API::debug_print("arr1[1] = " + std::to_string(arr1[1]));
  std::snprintf(buffer, sizeof(buffer), "%p", static_cast<void *>(arr1.data()));
  pointer_string = buffer;
  IC_API::debug_print("arr1.data() address = " + pointer_string);

  IC_API::debug_print(" ");
  IC_API::debug_print("p_nd_i1[0] = " + std::to_string(p_nd_i1[0]));
  IC_API::debug_print("p_nd_i1[1] = " + std::to_string(p_nd_i1[1]));
  std::snprintf(buffer, sizeof(buffer), "%p", static_cast<void *>(p_nd_i1));
  pointer_string = buffer;
  IC_API::debug_print("p_nd_i1 address = " + pointer_string);

  IC_API::debug_print(" ");
  IC_API::debug_print("p_cf_i1[0] = " + std::to_string(p_cf_i1[0]));
  IC_API::debug_print("p_cf_i1[1] = " + std::to_string(p_cf_i1[1]));
  std::snprintf(buffer, sizeof(buffer), "%p", static_cast<void *>(p_cf_i1));
  pointer_string = buffer;
  IC_API::debug_print("p_cf_i1 address = " + pointer_string);

  IC_API::debug_print(" ");
  IC_API::debug_print("(*p_vec1).size() = " + std::to_string((*p_vec1).size()));
  IC_API::debug_print("(*p_vec1)[0] = " + std::to_string((*p_vec1)[0]));
  IC_API::debug_print("(*p_vec1)[1] = " + std::to_string((*p_vec1)[1]));
  std::snprintf(buffer, sizeof(buffer), "%p",
                static_cast<void *>((*p_vec1).data()));
  pointer_string = buffer;
  IC_API::debug_print("(*p_vec1).data() address = " + pointer_string);

  IC_API::debug_print(" ");
  IC_API::debug_print("p_vec2->vec.size() = " +
                      std::to_string(p_vec2->vec.size()));
  IC_API::debug_print("p_vec2->vec[0] = " + std::to_string(p_vec2->vec[0]));
  IC_API::debug_print("p_vec2->vec[1] = " + std::to_string(p_vec2->vec[1]));
  std::snprintf(buffer, sizeof(buffer), "%p",
                static_cast<void *>(p_vec2->vec.data()));
  pointer_string = buffer;
  IC_API::debug_print("p_vec2->vec.data() address = " + pointer_string);

  // Outcomment if you want to test
  // IC_API::debug_print(" ");
  // IC_API::debug_print("vec1.size() = " + std::to_string(vec1.size()));
  // IC_API::debug_print("vec1[0] = " + std::to_string(vec1[0]));
  // IC_API::debug_print("vec1[1] = " + std::to_string(vec1[1]));
  // std::snprintf(buffer, sizeof(buffer), "%p", static_cast<void *>(vec1.data()));
  // pointer_string = buffer;
  // IC_API::debug_print("vec1.data() address = " + pointer_string);

  // IC_API::debug_print(" ");
  // IC_API::debug_print("vec101.vec.size() = " +
  //                     std::to_string(vec101.vec.size()));
  // IC_API::debug_print("vec101.vec[0] = " + std::to_string(vec101.vec[0]));
  // IC_API::debug_print("vec101.vec[1] = " + std::to_string(vec101.vec[1]));
  // std::snprintf(buffer, sizeof(buffer), "%p",
  //               static_cast<void *>(vec101.vec.data()));
  // pointer_string = buffer;
  // IC_API::debug_print("vec101.vec.data() address = " + pointer_string);
}

// -----------------------------------------------------------------------
// Canister endpoints

void change_memory() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  // Reset the self managed memory
  delete_memory();
  new_memory();

  print_it(std::string(__func__));
  change_it();
  print_it(std::string(__func__));

  ic_api.to_wire();
}

void print_memory() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  print_it(std::string(__func__));
  ic_api.to_wire();
}
