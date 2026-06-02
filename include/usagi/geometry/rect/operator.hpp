#pragma once

#include <usagi/concepts/geometry.hpp>
#include <usagi/geometry/rect/rect.hpp>

namespace usagi::geometry {
/// Returns whether two rectangle-like objects have the same edges.
///
/// @param lhs Left-hand rectangle-like input.
/// @param rhs Right-hand rectangle-like input.
/// @return `true` when left, top, right, and bottom are equal; otherwise `false`.
inline constexpr bool operator==(const usagi::concepts::geometry::rect_concept auto &lhs,
                                 const usagi::concepts::geometry::rect_concept auto &rhs) {
  return lhs.l() == rhs.l() && lhs.r() == rhs.r() && lhs.t() == rhs.t() && lhs.b() == rhs.b();
}

/// Returns whether two rectangle-like objects differ in any edge.
///
/// @param lhs Left-hand rectangle-like input.
/// @param rhs Right-hand rectangle-like input.
/// @return `true` when any edge differs; otherwise `false`.
inline constexpr bool operator!=(const usagi::concepts::geometry::rect_concept auto &lhs,
                                 const usagi::concepts::geometry::rect_concept auto &rhs) {
  return !(lhs == rhs);
}

/// Translates a rectangle by a point-like offset.
///
/// @param lhs Rectangle to translate.
/// @param rhs Point-like offset whose x and y are added to each edge.
/// @return Rectangle translated by `rhs`.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto)
operator+(const usagi::geometry::rect<ValueType> &lhs,
          const usagi::concepts::geometry::point_concept auto &rhs) {
  return usagi::geometry::rect<ValueType>{lhs.l() + rhs.x(), lhs.t() + rhs.y(), lhs.r() + rhs.x(),
                                          lhs.b() + rhs.y()};
}

/// Translates a rectangle by the negated point-like offset.
///
/// @param lhs Rectangle to translate.
/// @param rhs Point-like offset whose x and y are subtracted from each edge.
/// @return Rectangle translated by `-rhs`.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto)
operator-(const usagi::geometry::rect<ValueType> &lhs,
          const usagi::concepts::geometry::point_concept auto &rhs) {
  return usagi::geometry::rect<ValueType>{lhs.l() - rhs.x(), lhs.t() - rhs.y(), lhs.r() - rhs.x(),
                                          lhs.b() - rhs.y()};
}
} // namespace usagi::geometry
