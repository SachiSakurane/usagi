#pragma once

#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/geometry/point/point.hpp>

namespace usagi::geometry {
/// Returns whether two point-like objects have the same coordinates.
///
/// @param lhs Left-hand point-like input.
/// @param rhs Right-hand point-like input.
/// @return `true` when x and y are equal; otherwise `false`.
inline constexpr bool operator==(const usagi::concepts::geometry::point_concept auto &lhs,
                                 const usagi::concepts::geometry::point_concept auto &rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

/// Returns whether two point-like objects differ in either coordinate.
///
/// @param lhs Left-hand point-like input.
/// @param rhs Right-hand point-like input.
/// @return `true` when x or y differs; otherwise `false`.
inline constexpr bool operator!=(const usagi::concepts::geometry::point_concept auto &lhs,
                                 const usagi::concepts::geometry::point_concept auto &rhs) {
  return !(lhs == rhs);
}

/// Defines component-wise arithmetic operators for points and scalars.
///
/// Each generated overload takes either `(scalar, point)`, `(point, scalar)`, or
/// `(point, point)` inputs and returns a point whose x and y coordinates are
/// computed component-wise with the selected operator.
#define USAGI_POINT_OPERATORS(OP)                                                                  \
  template <usagi::concepts::arithmetic ValueType>                                                 \
  inline constexpr decltype(auto) operator OP(ValueType lhs,                                       \
                                              const usagi::geometry::point<ValueType> &rhs) {      \
    return usagi::geometry::point<ValueType>{lhs OP rhs.x(), lhs OP rhs.y()};                      \
  }                                                                                                \
  template <usagi::concepts::arithmetic ValueType>                                                 \
  inline constexpr decltype(auto) operator OP(const usagi::geometry::point<ValueType> &lhs,        \
                                              ValueType rhs) {                                     \
    return usagi::geometry::point<ValueType>{lhs.x() OP rhs, lhs.y() OP rhs};                      \
  }                                                                                                \
  template <usagi::concepts::arithmetic ValueType>                                                 \
  inline constexpr decltype(auto) operator OP(const usagi::geometry::point<ValueType> &lhs,        \
                                              const usagi::geometry::point<ValueType> &rhs) {      \
    return usagi::geometry::point<ValueType>{lhs.x() OP rhs.x(), lhs.y() OP rhs.y()};              \
  }

USAGI_POINT_OPERATORS(+)
USAGI_POINT_OPERATORS(-)
USAGI_POINT_OPERATORS(*)
USAGI_POINT_OPERATORS(/)

#undef USAGI_POINT_OPERATORS

} // namespace usagi::geometry
