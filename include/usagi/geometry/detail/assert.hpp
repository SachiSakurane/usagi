#pragma once

#include <cassert>
#include <type_traits>

namespace usagi::geometry::detail {
/// Asserts that a divisor is not zero.
///
/// @param value Divisor value to validate.
/// @throws const char* during constant evaluation when `value` is zero.
template <class ValueType>
inline constexpr void assert_nonzero_divisor(ValueType value) {
  if (std::is_constant_evaluated()) {
    if (value == static_cast<ValueType>(0)) {
      throw "division by zero";
    }
  } else {
    assert(value != static_cast<ValueType>(0));
  }
}

/// Asserts that a divisor is positive.
///
/// @param value Divisor value to validate.
/// @throws const char* during constant evaluation when `value` is not positive.
template <class ValueType>
inline constexpr void assert_positive_divisor(ValueType value) {
  if (std::is_constant_evaluated()) {
    if (!(value > static_cast<ValueType>(0))) {
      throw "division by zero";
    }
  } else {
    assert(value > static_cast<ValueType>(0));
  }
}
} // namespace usagi::geometry::detail
