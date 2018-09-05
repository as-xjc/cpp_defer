#pragma once

#include <functional>

/**
 * 延迟类
 *
 * @brief 模拟 golang 的 defer，方便处理一些延迟操作
 */
class Defer final {
 public:
  Defer() {}
  ~Defer() { if (cb_) cb_(); }

  Defer(const Defer& other) = delete;
  Defer& operator=(const Defer&) = delete;

  Defer(Defer&& other) = delete;
  Defer& operator=(Defer&& other) = delete;

  explicit Defer(std::function<void()>&& cb) {
    cb_ = std::move(cb);
  }

 private:
    std::function<void()> cb_;
};

#define __CPP_DEFER_CAT(a, b) a##b
#define _CPP_DEFER_CAT(a, b) __CPP_DEFER_CAT(a, b)

#define DEFER(cmd) ::Defer _CPP_DEFER_CAT(__go_defer__, __LINE__)([&]() { cmd; })
#define DEFER_CLASS(cmd) ::Defer _CPP_DEFER_CAT(__go_defer_class__, __LINE__)([&, this]() { cmd; })
