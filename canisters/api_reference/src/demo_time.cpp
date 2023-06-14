/* file: src/demo_time.cpp

$ dfx canister call --type idl --output idl demo demo_time '()'
("The current system time in nanoseconds: 1684265399218380314 (2023-5-16 19:29:59)")

*/
#include "demo_time.h"
#include "ic_api.h"
#include <ctime>
#include <sstream>

std::string format_time(uint64_t time_in_ns) {
  /* 
  https://internetcomputer.org/docs/current/references/ic-interface-spec#system-api-time
  The time is given as nanoseconds since 1970-01-01. 
  - The IC guarantees that the time, as observed by the canister, is monotonically increasing, 
    even across canister upgrades. 
  - Within an invocation of one entry point, the time is constant. 
  - The system times of different canisters are unrelated, and calls from one canister to another 
    may appear to travel “backwards in time”.
  - The IC is decentralized and has no notion of a timezone.
  */
  std::time_t time_in_s = time_in_ns / 1'000'000'000;
  std::tm *tm = std::gmtime(&time_in_s);

  // Format the time manually
  std::string formatted_time = "";
  formatted_time += std::to_string(tm->tm_year + 1900); // Year
  formatted_time += "-";
  formatted_time += std::to_string(tm->tm_mon + 1); // Month
  formatted_time += "-";
  formatted_time += std::to_string(tm->tm_mday); // Day
  formatted_time += " ";
  formatted_time += std::to_string(tm->tm_hour); // Hour
  formatted_time += ":";
  formatted_time += std::to_string(tm->tm_min); // Minute
  formatted_time += ":";
  formatted_time += std::to_string(tm->tm_sec); // Second

  return formatted_time;
}

void demo_time() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  CandidTypePrincipal caller = ic_api.get_caller();

  uint64_t time_in_ns = ic_api.time();

  std::string msg;
  msg.append("The current system time in nanoseconds: " +
             std::to_string(time_in_ns) + " (" + format_time(time_in_ns) + ")");

  IC_API::debug_print(msg);
  ic_api.to_wire(CandidTypeText(msg));
}