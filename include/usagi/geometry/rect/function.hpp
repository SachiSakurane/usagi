#pragma once

#include <algorithm>

#include <usagi/concepts/geometry.hpp>
#include <usagi/geometry/rect/rect.hpp>

namespace usagi::geometry
{
  inline constexpr bool contain(const usagi::concepts::geometry::rect_concept auto &r, const usagi::concepts::geometry::point_concept auto &p)
  {
    return (r.l() <= p.x() && p.x() <= r.r()) && (r.t() <= p.y() && p.y() <= r.b());
  }

  template <usagi::concepts::geometry::rect_concept RectType>
  inline constexpr decltype(auto) padding(const RectType &rect, typename RectType::value_type v)
  {
    return usagi::geometry::tupled_rect<typename RectType::value_type>{
        [rect, v]()
        {
          auto l = rect.l() + v;
          auto t = rect.t() + v;
          auto r = rect.r() - v;
          auto b = rect.b() - v;
          bool w = l < r;
          bool h = t < b;
          return std::make_tuple(
              w ? l : (l + r) / static_cast<typename RectType::value_type>(2),
              h ? t : (t + b) / static_cast<typename RectType::value_type>(2),
              w ? r : (l + r) / static_cast<typename RectType::value_type>(2),
              h ? b : (t + b) / static_cast<typename RectType::value_type>(2));
        }};
  }
}
