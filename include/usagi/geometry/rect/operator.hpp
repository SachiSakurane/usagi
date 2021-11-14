#pragma once

#include <usagi/concepts/geometry.hpp>
#include <usagi/geometry/rect/rect.hpp>

namespace usagi::geometry {
inline constexpr bool operator==(const usagi::concepts::geometry::rect_concept auto &lhs,
                                 const usagi::concepts::geometry::rect_concept auto &rhs) {
  return lhs.l() == rhs.l() && lhs.r() == rhs.r() && lhs.t() == rhs.t() && lhs.b() == rhs.b();
}

inline constexpr bool operator!=(const usagi::concepts::geometry::rect_concept auto &lhs,
                                 const usagi::concepts::geometry::rect_concept auto &rhs) {
  return !(lhs == rhs);
}

template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto)
operator+(const usagi::geometry::rect<ValueType> &lhs,
          const usagi::concepts::geometry::point_concept auto &rhs) {
  return usagi::geometry::rect<ValueType>{lhs.l() + rhs.x(), lhs.t() + rhs.y(), lhs.r() + rhs.x(),
                                          lhs.b() + rhs.y()};
}

template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto)
operator-(const usagi::geometry::rect<ValueType> &lhs,
          const usagi::concepts::geometry::point_concept auto &rhs) {
  return usagi::geometry::rect<ValueType>{lhs.l() - rhs.x(), lhs.t() - rhs.y(), lhs.r() - rhs.x(),
                                          lhs.b() - rhs.y()};
}
} // namespace usagi::geometry
