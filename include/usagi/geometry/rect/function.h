#pragma once

#include <usagi/concepts/geometry.h>

namespace usagi
{
  inline constexpr bool contain(const usagi::concepts::geometry::rect_concept auto &r, const usagi::concepts::geometry::point_concept auto &p)
  {
    return (r.l() <= p.x() && p.x() <= r.r()) && (r.t() <= p.y() && p.y() <= r.b());
  }
}
