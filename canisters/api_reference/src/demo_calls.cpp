/* file: src/demo_calls.cpp

$ icp canister call demo demo_call '("C++")' --environment local
("The callee replied: Hello, C++!")

$ icp canister call demo demo_yield '(3 : nat32)' --environment local
(
  "Instructions per message: 1207587 1074949 1074599. The whole call: 3613406 instructions.",
)

$ icp canister call demo demo_long_compute '(150 : nat32)' --environment local
(
  "150B instructions in 8 messages, at most 20B each. One message can execute at most 40B. Result: 11403713523426525226",
)

*/
#include "demo_calls.h"
#include "ic_api.h"

#include <string>

// Calls demo_call_callee of this canister, and replies with its reply.
// demo_call is a coroutine: it starts in the update call, and continues in
// the callback of the call it awaits.
IC_Async demo_call_async() {
  IC_API ic_api(CanisterUpdate{"demo_call"}, false);
  std::string name;
  ic_api.from_wire(CandidTypeText{&name});

  // Any canister can be called; here, the canister itself
  IC_CallResult<IC_CallReply> result =
      co_await IC_Call::bounded_wait(ic_api.get_canister_self(),
                                     "demo_call_callee")
          .with_arg(CandidTypeText{name});
  if (!result) {
    ic_api.to_wire(
        CandidTypeText{"The call failed: " + result.error().to_string()});
    co_return;
  }
  std::string greeting;
  result->decode(CandidTypeText{&greeting});
  ic_api.to_wire(CandidTypeText{"The callee replied: " + greeting});
}
void demo_call() { demo_call_async(); }

void demo_call_callee() {
  IC_API ic_api(CanisterUpdate{std::string(__func__)}, false);
  std::string name;
  ic_api.from_wire(CandidTypeText{&name});
  ic_api.to_wire(CandidTypeText{"Hello, " + name + "!"});
}

// Continues in a new message after every yield, so a long computation
// is not stopped by the instruction limit of one message.
IC_Async demo_yield_async() {
  IC_API ic_api(CanisterUpdate{"demo_yield"}, false);
  uint32_t n{0};
  ic_api.from_wire(CandidTypeNat32{&n});
  if (n > 10) {
    IC_API::trap("demo_yield: at most 10 yields");
  }

  std::string msg = "Instructions per message:";
  for (uint32_t i = 0; i < n; ++i) {
    // A chunk of work...
    volatile uint64_t sum = 0;
    for (uint64_t k = 0; k < 100'000; ++k)
      sum += k;
    msg += " " + std::to_string(IC_API::performance_counter());
    // ...then continue in a new message, with a fresh instruction limit
    IC_CallResult<void> yielded = co_await ic_api.yield_fresh_budget();
    yielded.value();
  }
  msg += ". The whole call: " +
         std::to_string(IC_API::performance_counter(
             IC_API::PerformanceCounterType::CallContextInstructions)) +
         " instructions.";
  ic_api.to_wire(CandidTypeText{msg});
}
void demo_yield() { demo_yield_async(); }

// A computation of `billions` billion instructions: up to 200B, five times
// the 40B limit of one message. It runs in chunks of at most 20B
// instructions, with a yield after each, and replies once it is done.
// It burns cycles, so only a controller may call it.
IC_Async demo_long_compute_async() {
  IC_API ic_api(CanisterUpdate{"demo_long_compute"}, false);
  uint32_t billions{0};
  ic_api.from_wire(CandidTypeNat32{&billions});
  if (!ic_api.is_controller(ic_api.get_caller())) {
    IC_API::trap("demo_long_compute: only a controller may call it");
  }
  if (billions > 200) {
    IC_API::trap("demo_long_compute: at most 200 billion instructions");
  }
  const uint64_t target = uint64_t{billions} * 1'000'000'000;
  const uint64_t chunk = 20'000'000'000;

  auto total = [] {
    return IC_API::performance_counter(
        IC_API::PerformanceCounterType::CallContextInstructions);
  };

  // The state of the computation: an LCG, x = a * x + c (mod 2^64).
  // It lives in the coroutine, so it survives the yields.
  uint64_t x = 42;
  uint32_t messages = 0;
  while (true) {
    ++messages;
    // A chunk of work, until this message executed `chunk` instructions,
    // or the whole call `target` instructions...
    do {
      for (int i = 0; i < 65536; ++i)
        x = 6364136223846793005ULL * x + 1442695040888963407ULL;
    } while (IC_API::performance_counter() < chunk && total() < target);
    if (total() >= target) break;
    // ...then continue in a new message, with a fresh instruction limit
    IC_CallResult<void> yielded = co_await ic_api.yield_fresh_budget();
    yielded.value();
  }
  ic_api.to_wire(CandidTypeText{
      std::to_string(total() / 1'000'000'000) + "B instructions in " +
      std::to_string(messages) +
      " messages, at most 20B each. One message can execute at most 40B. "
      "Result: " +
      std::to_string(x)});
}
void demo_long_compute() { demo_long_compute_async(); }
