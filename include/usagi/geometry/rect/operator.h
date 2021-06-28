#pragma once

#include <usagi/concepts/geometry.h>
#include <usagi/geometry/rect/rect.h>

namespace usagi
{
  inline constexpr bool operator==(const usagi::concepts::geometry::rect_concept auto &lhs, const usagi::concepts::geometry::rect_concept auto &rhs)
  {
    return lhs.l() == rhs.l() && lhs.r() == rhs.r() && lhs.t() == rhs.t() && lhs.b() == rhs.b();
  }

  inline constexpr bool operator!=(const usagi::concepts::geometry::rect_concept auto &lhs, const usagi::concepts::geometry::rect_concept auto &rhs)
  {
    return !(lhs == rhs);
  }

  template <usagi::concepts::geometry::rect_concept RectType>
  inline constexpr decltype(auto) operator+(const RectType &lhs, const usagi::concepts::geometry::point_concept auto &rhs)
  {
    return usagi::rect<typename RectType::value_type>{
        [lhs, rhs]()
        { return lhs.l() + rhs.x(); },
        [lhs, rhs]()
        { return lhs.t() + rhs.y(); },
        [lhs, rhs]()
        { return lhs.r() + rhs.x(); },
        [lhs, rhs]()
        { return lhs.b() + rhs.y(); }};
  }

  template <usagi::concepts::geometry::rect_concept RectType>
  inline constexpr decltype(auto) operator-(const RectType &lhs, const usagi::concepts::geometry::point_concept auto &rhs)
  {
    return usagi::rect<typename RectType::value_type>{
        [lhs, rhs]()
        { return lhs.l() - rhs.x(); },
        [lhs, rhs]()
        { return lhs.t() - rhs.y(); },
        [lhs, rhs]()
        { return lhs.r() - rhs.x(); },
        [lhs, rhs]()
        { return lhs.b() - rhs.y(); }};
  }
}
