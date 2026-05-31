#pragma once

#include <cassert>

#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/geometry/detail/assert.hpp>
#include <usagi/geometry/size/size.hpp>

namespace usagi::geometry {
inline constexpr bool operator==(const usagi::concepts::geometry::size_concept auto &lhs,
                                 const usagi::concepts::geometry::size_concept auto &rhs) {
  return lhs.width() == rhs.width() && lhs.height() == rhs.height();
}

inline constexpr bool operator!=(const usagi::concepts::geometry::size_concept auto &lhs,
                                 const usagi::concepts::geometry::size_concept auto &rhs) {
  return !(lhs == rhs);
}

template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator+(const usagi::geometry::size<ValueType> &lhs,
                                          const usagi::geometry::size<ValueType> &rhs) {
  return usagi::geometry::size<ValueType>{lhs.width() + rhs.width(), lhs.height() + rhs.height()};
}

template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator-(const usagi::geometry::size<ValueType> &lhs,
                                          const usagi::geometry::size<ValueType> &rhs) {
  return usagi::geometry::size<ValueType>{lhs.width() - rhs.width(), lhs.height() - rhs.height()};
}

template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator*(ValueType lhs,
                                          const usagi::geometry::size<ValueType> &rhs) {
  assert(lhs >= 0);
  return usagi::geometry::size<ValueType>{lhs * rhs.width(), lhs * rhs.height()};
}

template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator*(const usagi::geometry::size<ValueType> &lhs,
                                          ValueType rhs) {
  assert(rhs >= 0);
  return usagi::geometry::size<ValueType>{lhs.width() * rhs, lhs.height() * rhs};
}

template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator/(ValueType lhs,
                                          const usagi::geometry::size<ValueType> &rhs) {
  assert(lhs >= 0);
  detail::assert_nonzero_divisor(rhs.width());
  detail::assert_nonzero_divisor(rhs.height());
  return usagi::geometry::size<ValueType>{lhs / rhs.width(), lhs / rhs.height()};
}

template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) operator/(const usagi::geometry::size<ValueType> &lhs,
                                          ValueType rhs) {
  detail::assert_positive_divisor(rhs);
  return usagi::geometry::size<ValueType>{lhs.width() / rhs, lhs.height() / rhs};
}

} // namespace usagi::geometry
