#pragma once

namespace usagi::geometry {
/// Returns a duplicated value from a geometry-like object.
///
/// @param x Geometry-like object that provides `duplicate()`.
/// @return Result of `x.duplicate()`.
template <class GeometryType>
inline constexpr decltype(auto) duplicate(const GeometryType &x) {
  return x.duplicate();
}
} // namespace usagi::geometry
