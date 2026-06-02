#pragma once

#include <functional>
#include <type_traits>

namespace usagi {
/// Stores either a value or a nullary callable and exposes it as a nullary callable.
///
/// @tparam ValueType Value produced by the variable.
template <class ValueType>
struct variable {
  /// Produced value type.
  using value_type = ValueType;

  /// Creates a variable that evaluates to zero.
  variable() : functor{[]() { return static_cast<value_type>(0); }} {}

  /// Creates a variable that always evaluates to `v`.
  ///
  /// @param v Stored value returned by `operator()`.
  variable(const value_type &v) : functor{[v]() { return v; }} {}

  /// Creates a variable from a nullary callable.
  ///
  /// @param f Callable returning `ValueType`.
  template <class FunctionType,
            class = std::enable_if_t<std::is_same_v<ValueType, std::invoke_result_t<FunctionType>>>>
  variable(FunctionType &&f) : functor{std::move(f)} {}

  /// Evaluates the stored value source.
  ///
  /// @return Value produced by the stored callable.
  decltype(auto) operator()() const { return functor(); }

private:
  std::function<value_type()> functor;
};

/// Deduces `variable<ValueType>` from a stored value.
template <class ValueType>
variable(const ValueType &) -> variable<ValueType>;

/// Deduces `variable<Result>` from a nullary callable.
template <class FunctionType>
variable(FunctionType &&) -> variable<std::invoke_result_t<FunctionType>>;
} // namespace usagi
