#pragma once

namespace usagi::utility {
consteval void eval_assert(bool expr) {
  if (!expr) {
    struct {
      void fail() {}
    } not_const;
    not_const.fail();
  }
}

consteval void eval_true(bool expr) { eval_assert(expr); }
consteval void eval_false(bool expr) { eval_assert(!expr); }
} // namespace usagi::utility
