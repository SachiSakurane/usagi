#pragma once

#include <cassert>

#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/geometry/detail/assert.hpp>
#include <usagi/geometry/size/size.hpp>

namespace usagi::geometry {
/// Returns whether two size-like objects have the same width and height.
///
/// @param lhs Left-hand size-like input.
/// @param rhs Right-hand size-like input.
/// @return `true` when width and height are equal; otherwise `false`.
inline constexpr bool operator==(const usagi::concepts::geometry::size_concept auto &lhs,
                                 const usagi::concepts::geometry::size_concept auto &rhs) {
  return lhs.width() == rhs.width() && lhs.height() == rhs.height();
}

/// Returns whether two size-like objects differ in width or height.
///
/// @param lhs Left-hand size-like input.
/// @param rhs Right-hand size-like input.
/// @return `true` when width or height differs; otherwise `false`.
inline constexpr bool operator!=(const usagi::concepts::geometry::size_concept auto &lhs,
                                 const usagi::concepts::geometry::size_concept auto &rhs) {
  return !(lhs == rhs);
}

/// Adds two sizes component-wise.
///
/// @param lhs Left-hand size.
/// @param rhs Right-hand size.
/// @return Size whose width and height are the component-wise sums.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator+(const usagi::geometry::size<ValueType> &lhs,
                                          const usagi::geometry::size<ValueType> &rhs) {
  return usagi::geometry::size<ValueType>{lhs.width() + rhs.width(), lhs.height() + rhs.height()};
}

/// Subtracts two sizes component-wise.
///
/// @param lhs Left-hand size.
/// @param rhs Right-hand size.
/// @return Size whose width and height are the component-wise differences.
/// @pre The resulting width and height must be non-negative.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator-(const usagi::geometry::size<ValueType> &lhs,
                                          const usagi::geometry::size<ValueType> &rhs) {
  return usagi::geometry::size<ValueType>{lhs.width() - rhs.width(), lhs.height() - rhs.height()};
}

/// Multiplies each size component by a non-negative scalar.
///
/// @param lhs Scalar multiplier.
/// @param rhs Size to scale.
/// @return Size whose width and height are multiplied by `lhs`.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator*(ValueType lhs,
                                          const usagi::geometry::size<ValueType> &rhs) {
  assert(lhs >= 0);
  return usagi::geometry::size<ValueType>{lhs * rhs.width(), lhs * rhs.height()};
}

/// Multiplies each size component by a non-negative scalar.
///
/// @param lhs Size to scale.
/// @param rhs Scalar multiplier.
/// @return Size whose width and height are multiplied by `rhs`.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator*(const usagi::geometry::size<ValueType> &lhs,
                                          ValueType rhs) {
  assert(rhs >= 0);
  return usagi::geometry::size<ValueType>{lhs.width() * rhs, lhs.height() * rhs};
}

/// Divides a non-negative scalar by each size component.
///
/// @param lhs Scalar numerator.
/// @param rhs Size providing width and height divisors.
/// @return Size containing `lhs / rhs.width()` and `lhs / rhs.height()`.
/// @pre The scalar and both size components must be valid divisors for the value type.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator/(ValueType lhs,
                                          const usagi::geometry::size<ValueType> &rhs) {
  assert(lhs >= 0);
  detail::assert_nonzero_divisor(rhs.width());
  detail::assert_nonzero_divisor(rhs.height());
  return usagi::geometry::size<ValueType>{lhs / rhs.width(), lhs / rhs.height()};
}

/// Divides each size component by a positive scalar.
///
/// @param lhs Size to divide.
/// @param rhs Scalar divisor.
/// @return Size whose width and height are divided by `rhs`.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator/(const usagi::geometry::size<ValueType> &lhs,
                                          ValueType rhs) {
  detail::assert_positive_divisor(rhs);
  return usagi::geometry::size<ValueType>{lhs.width() / rhs, lhs.height() / rhs};
}

} // namespace usagi::geometry
