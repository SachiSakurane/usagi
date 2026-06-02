#pragma once

namespace usagi::utility {
/// Fails constant evaluation when `expr` is false.
///
/// @param expr Condition that must evaluate to `true`.
consteval void eval_assert(bool expr) {
  if (!expr) {
    struct {
      void fail() {}
    } not_const;
    not_const.fail();
  }
}

/// Requires a compile-time expression to be true.
///
/// @param expr Condition that must evaluate to `true`.
consteval void eval_true(bool expr) { eval_assert(expr); }

/// Requires a compile-time expression to be false.
///
/// @param expr Condition that must evaluate to `false`.
consteval void eval_false(bool expr) { eval_assert(!expr); }
} // namespace usagi::utility
