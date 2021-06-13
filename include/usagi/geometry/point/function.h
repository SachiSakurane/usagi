#pragma once

#include <cmath>

#include <usagi/geometry/point/point.h>

namespace usagi
{
  template <class PointType>
  inline constexpr decltype(auto) distance(const PointType &a, const PointType &b)
  {
    auto x_sub = a.x - b.x;
    auto y_sub = a.y - b.y;
    return std::sqrt(x_sub * x_sub + y_sub * y_sub);
  }
}
