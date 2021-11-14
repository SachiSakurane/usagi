#pragma once

#include <cmath>
#include <type_traits>

#include <usagi/geometry/point/point.hpp>

namespace usagi::geometry {
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) distance(const usagi::geometry::point<ValueType> &a,
                                         const usagi::geometry::point<ValueType> &b) {
  auto x_sub = a.x() - b.x();
  auto y_sub = a.y() - b.y();
  return std::sqrt(x_sub * x_sub + y_sub * y_sub);
}
} // namespace usagi::geometry
