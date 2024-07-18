// Exploration of orthogonal persistence for various C++ data structures

#include "memory.h"
#include "ic_api.h"

#include <iostream>
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
// -- vector
std::vector<uint64_t> *p_vec1{nullptr};
// -- string
std::string *p_str1{nullptr};

// -- vector wrapped in a class
class MyVec {
public:
  MyVec() : vec{0, 0} {}
  std::vector<uint64_t> vec;
};
MyVec *p_vec2{nullptr};

// -- string wrapped in a class
class MyString {
public:
  std::string str;
};
MyString *p_str2{nullptr};

// -- const map wrapped in a struct
struct MyMap {
  const std::map<int, const char *> map = {
      {0, "item-0"}, {1, "item-1"}, {2, "item-2"}};
};
MyMap *p_map{nullptr};

// --
// Standard library data structures that keep data on the heap can NOT
// be defined in the global/static section of the code:
// -> Values are not persisted after an update call.
// -> Just adding them here corrupts memory of the canister, and you will
//    get this message when calling the endpoints:
/*
Error: Failed query call.
Caused by: The replica returned a rejection error: reject code CanisterError, 
           reject message IC0502: Error from Canister bkyz2-fmaaa-aaaaa-qaaaq-cai: 
           Canister trapped: heap out of bounds, error code Some("IC0502")
*/
// std::vector<uint64_t> vec1(2, 0);
// MyVec vec101;
// static const std::map<int, const char *> map1 = {
//     {0, "item-0"}, {1, "item-1"}, {2, "item-2"}};

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
  p_str1 = new (std::nothrow) std::string();
  if (p_str1 == nullptr) {
    IC_API::trap("Allocation of p_str1 failed");
  }

  p_vec2 = new (std::nothrow) MyVec();
  if (p_vec2 == nullptr) {
    IC_API::trap("Allocation of p_vec2 failed");
  }
  p_str2 = new (std::nothrow) MyString();
  if (p_str2 == nullptr) {
    IC_API::trap("Allocation of p_str2 failed");
  }

  p_map = new (std::nothrow) MyMap();
  if (p_map == nullptr) {
    IC_API::trap("Allocation of p_map failed");
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
  if (p_str1) {
    delete p_str1;
    p_str1 = nullptr;
  }

  if (p_vec2) {
    delete p_vec2;
    p_vec2 = nullptr;
  }
  if (p_str2) {
    delete p_str2;
    p_str2 = nullptr;
  }

  if (p_map) {
    delete p_map;
    p_map = nullptr;
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

  *p_str1 = "String value: '" + std::to_string(i1) + "'";

  ++p_vec2->vec[0];
  ++p_vec2->vec[1];

  p_str2->str = "String value: '" + std::to_string(i1) + "'";

  // Outcomment these will lead to HEAP OUT OF BOUND
  // ++vec1[0];
  // ++vec1[1];

  // ++vec101.vec[0];
  // ++vec101.vec[1];
}

void print_it(std::string calling_function) {
  char buffer[200]; // Make sure the buffer is large enough
  std::string address;

  std::cout << "------" << std::endl;
  std::cout << calling_function + ":" << std::endl;

  std::cout << " " << std::endl;
  std::cout << "i1 = " + std::to_string(i1) << std::endl;

  std::cout << " " << std::endl;
  std::cout << "arr1.size() = " + std::to_string(arr1.size()) << std::endl;
  std::cout << "arr1[0] = " + std::to_string(arr1[0]) << std::endl;
  std::cout << "arr1[1] = " + std::to_string(arr1[1]) << std::endl;
  std::snprintf(buffer, sizeof(buffer), "%p", static_cast<void *>(arr1.data()));
  address = buffer;
  std::cout << "arr1.data() address = " + address << std::endl;

  std::cout << " " << std::endl;
  std::cout << "p_nd_i1[0] = " + std::to_string(p_nd_i1[0]) << std::endl;
  std::cout << "p_nd_i1[1] = " + std::to_string(p_nd_i1[1]) << std::endl;
  std::snprintf(buffer, sizeof(buffer), "%p", static_cast<void *>(p_nd_i1));
  address = buffer;
  std::cout << "p_nd_i1 address = " + address << std::endl;

  std::cout << " " << std::endl;
  std::cout << "p_cf_i1[0] = " + std::to_string(p_cf_i1[0]) << std::endl;
  std::cout << "p_cf_i1[1] = " + std::to_string(p_cf_i1[1]) << std::endl;
  std::snprintf(buffer, sizeof(buffer), "%p", static_cast<void *>(p_cf_i1));
  address = buffer;
  std::cout << "p_cf_i1 address = " + address << std::endl;

  std::cout << " " << std::endl;
  std::cout << "(*p_vec1).size() = " + std::to_string((*p_vec1).size())
            << std::endl;
  std::cout << "(*p_vec1)[0] = " + std::to_string((*p_vec1)[0]) << std::endl;
  std::cout << "(*p_vec1)[1] = " + std::to_string((*p_vec1)[1]) << std::endl;
  std::snprintf(buffer, sizeof(buffer), "%p",
                static_cast<void *>((*p_vec1).data()));
  address = buffer;
  std::cout << "(*p_vec1).data() address = " + address << std::endl;

  std::cout << " " << std::endl;
  std::cout << "p_str1 content = " + *p_str1 << std::endl;
  std::snprintf(buffer, sizeof(buffer), "%p", static_cast<void *>(p_str1));
  address = buffer;
  std::cout << "p_str1 address = " + address << std::endl;

  std::cout << " " << std::endl;
  std::cout << "p_vec2->vec.size() = " + std::to_string(p_vec2->vec.size())
            << std::endl;
  std::cout << "p_vec2->vec[0] = " + std::to_string(p_vec2->vec[0])
            << std::endl;
  std::cout << "p_vec2->vec[1] = " + std::to_string(p_vec2->vec[1])
            << std::endl;
  std::snprintf(buffer, sizeof(buffer), "%p",
                static_cast<void *>(p_vec2->vec.data()));
  address = buffer;
  std::cout << "p_vec2->vec.data() address = " + address << std::endl;

  std::cout << " " << std::endl;
  std::cout << "p_str2->str content = " + p_str2->str << std::endl;
  std::snprintf(buffer, sizeof(buffer), "%p", static_cast<void *>(p_str2));
  address = buffer;
  std::cout << "p_str2 address = " + address << std::endl;

  std::cout << " " << std::endl;
  std::cout << "p_map->map.size() = " << p_map->map.size() << std::endl;
  std::cout << "p_map->map.at(0)) = " << p_map->map.at(0) << std::endl;

  // Outcommenting these will lead to HEAP OUT OF BOUNDS
  // std::cout << " " << std::endl;
  // std::cout << "vec1.size() = " + std::to_string(vec1.size()) << std::endl;
  // std::cout << "vec1[0] = " + std::to_string(vec1[0]) << std::endl;
  // std::cout << "vec1[1] = " + std::to_string(vec1[1]) << std::endl;
  // std::snprintf(buffer, sizeof(buffer), "%p", static_cast<void *>(vec1.data()));
  // address = buffer;
  // std::cout << "vec1.data() address = " + address << std::endl;

  // std::cout << " " << std::endl;
  // std::cout << "vec101.vec.size() = " +
  //                     std::to_string(vec101.vec.size()) << std::endl;
  // std::cout << "vec101.vec[0] = " + std::to_string(vec101.vec[0]) << std::endl;
  // std::cout << "vec101.vec[1] = " + std::to_string(vec101.vec[1]) << std::endl;
  // std::snprintf(buffer, sizeof(buffer), "%p",
  //               static_cast<void *>(vec101.vec.data()));
  // address = buffer;
  // std::cout << "vec101.vec.data() address = " + address << std::endl;

  // std::cout << " " << std::endl;
  // std::cout << "map1.size() = " << map1.size() << std::endl;
  // std::cout << "map1.at(0)) = " << map1.at(0) << std::endl;
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
