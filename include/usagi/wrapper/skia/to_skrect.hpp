#pragma once

#include <usagi/concepts/geometry.hpp>

#include "include/core/SkRect.h"

namespace usagi::wrapper::skia {

/// Converts a size-like object to a Skia rectangle at the origin.
///
/// @param size Source width and height.
/// @return Skia rectangle with origin `(0, 0)` and the source size.
SkRect to_skrect(const usagi::concepts::geometry::size_concept auto &size) {
  return SkRect::MakeWH(size.width(), size.height());
}

/// Converts point and size-like objects to a Skia rectangle.
///
/// @param point Source top-left origin.
/// @param size Source width and height.
/// @return Skia rectangle using `point` as origin and `size` as dimensions.
SkRect to_skrect(const usagi::concepts::geometry::point_concept auto &point,
                 const usagi::concepts::geometry::size_concept auto &size) {
  return SkRect::MakeXYWH(point.x(), point.y(), size.width(), size.height());
}

/// Converts a rectangle-like object to a Skia rectangle.
///
/// @param rect Source left, top, right, and bottom edges.
/// @return Skia rectangle with the same edges.
SkRect to_skrect(const usagi::concepts::geometry::rect_concept auto &rect) {
  auto [l, t, r, b] = rect();
  return SkRect::MakeLTRB(l, t, r, b);
}

} // namespace usagi::wrapper::skia
