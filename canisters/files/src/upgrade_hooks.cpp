#include "upgrade_hooks.h"

#include <cstdint>
#include <fstream>
#include <string>

#include "ic_api.h"

// The hooks count the upgrades in a file: files survive an upgrade, while the
// Wasm heap does not.
namespace {
const char *HISTORY_PATH = "upgrade_history.txt";

struct UpgradeHistory {
  uint64_t pre_upgrade_count{0};
  uint64_t post_upgrade_count{0};
  std::string last_pre_upgrade_caller;
};

UpgradeHistory load_history() {
  UpgradeHistory history;
  std::ifstream file(HISTORY_PATH);
  file >> history.pre_upgrade_count >> history.post_upgrade_count >>
      history.last_pre_upgrade_caller;
  return history;
}

void save_history(const UpgradeHistory &history) {
  std::ofstream file(HISTORY_PATH, std::ios::trunc);
  file << history.pre_upgrade_count << " " << history.post_upgrade_count << " "
       << history.last_pre_upgrade_caller << "\n";
}
} // namespace

// docs start: upgrade_hooks
// Called on the OLD wasm, right before an upgrade replaces it.
// A trap here aborts the upgrade, and the old wasm stays installed.
void canister_pre_upgrade() {
  IC_API ic_api(CanisterPreUpgrade{std::string(__func__)}, false);

  UpgradeHistory history = load_history();
  history.pre_upgrade_count += 1;
  history.last_pre_upgrade_caller = ic_api.get_caller().get_text();
  save_history(history);
}

// Called on the NEW wasm, right after the upgrade installed it.
void canister_post_upgrade() {
  IC_API ic_api(CanisterPostUpgrade{std::string(__func__)}, false);

  UpgradeHistory history = load_history();
  history.post_upgrade_count += 1;
  save_history(history);
}
// docs end: upgrade_hooks

void upgrade_history() {
  IC_API ic_api(CanisterQuery{std::string(__func__)}, false);
  const UpgradeHistory history = load_history();

  CandidTypeRecord r_out;
  r_out.append("pre_upgrade_count", CandidTypeNat64{history.pre_upgrade_count});
  r_out.append("post_upgrade_count",
               CandidTypeNat64{history.post_upgrade_count});
  r_out.append("last_pre_upgrade_caller",
               CandidTypeText{history.last_pre_upgrade_caller});
  ic_api.to_wire(r_out);
}
