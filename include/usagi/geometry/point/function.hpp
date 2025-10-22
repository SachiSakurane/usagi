#pragma once

#include <cmath>
#include <type_traits>

#include <usagi/geometry/point/point.hpp>

namespace usagi::geometry {
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) distance(const usagi::geometry::point<ValueType> &a,
                                         const usagi::geometry::point<ValueType> &b) {
  return std::hypot(a.x() - b.x(), a.y() - b.y());
}
} // namespace usagi::geometry
