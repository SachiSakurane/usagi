#pragma once

namespace usagi::geometry {
template <class GeometryType>
inline constexpr decltype(auto) duplicate(const GeometryType &x) {
  return x.duplicate();
}
} // namespace usagi::geometry
