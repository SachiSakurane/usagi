#pragma once

#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/geometry/point/point.hpp>

namespace usagi::geometry {
inline constexpr bool operator==(const usagi::concepts::geometry::point_concept auto &lhs,
                                 const usagi::concepts::geometry::point_concept auto &rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

inline constexpr bool operator!=(const usagi::concepts::geometry::point_concept auto &lhs,
                                 const usagi::concepts::geometry::point_concept auto &rhs) {
  return !(lhs == rhs);
}

#define USAGI_POINT_OPERATORS(OP)                                                                  \
  template <usagi::utility::arithmetic ValueType>                                                  \
  inline constexpr decltype(auto) operator OP(ValueType lhs,                                       \
                                              const usagi::geometry::point<ValueType> &rhs) {      \
    return usagi::geometry::point<ValueType>{lhs OP rhs.x(), lhs OP rhs.y()};                      \
  }                                                                                                \
  template <usagi::utility::arithmetic ValueType>                                                  \
  inline constexpr decltype(auto) operator OP(const usagi::geometry::point<ValueType> &lhs,        \
                                              ValueType rhs) {                                     \
    return usagi::geometry::point<ValueType>{lhs.x() OP rhs, lhs.y() OP rhs};                      \
  }                                                                                                \
  template <usagi::utility::arithmetic ValueType>                                                  \
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
