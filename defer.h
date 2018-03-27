#pragma once

#include <vector>
#include <functional>

class Defer final {
 public:
  Defer() {}
  Defer(Defer& other) {
    this->cbs_ = std::move(other.cbs_);
  }

  Defer& operator=(Defer& other) noexcept {
    this->cbs_ = std::move(other.cbs_);
    return *this;
  };

  explicit Defer(std::function<void()>&& cb) {
    cbs_.emplace_back(std::move(cb));
  }
  ~Defer() {
    Done();
  }

  Defer& Then(std::function<void()>&& cb) {
    cbs_.emplace_back(std::move(cb));
    return *this;
  }

  void Done() {
    if (cbs_.empty()) return;

    for (auto it = cbs_.rbegin(); it != cbs_.rend(); ++it) {
      (*it)();
    }
    cbs_.clear();
  }

 private:
  std::vector<std::function<void()>> cbs_;
};

/**
 * use one times in a life scope only
 */
#define DEFER(cmd) ::Defer ___simulate_go_defer___([&]() { cmd; })

#define DEFER_IN_CLASS(cmd) ::Defer ___simulate_go_defer_class___([&, this]() { cmd; })
