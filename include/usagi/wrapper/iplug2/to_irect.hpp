#pragma once

#include <usagi/concepts/geometry.hpp>

namespace usagi::wrapper::iplug2 {
/// Converts a size-like object to an IPlug2 rectangle at the origin.
///
/// @param size Source width and height.
/// @return IPlug2 rectangle with origin `(0, 0)` and the source size.
iplug::igraphics::IRECT to_irect(const usagi::concepts::geometry::size_concept auto &size) {
  return iplug::igraphics::IRECT::MakeXYWH(0, 0, size.width(), size.height());
}

/// Converts point and size-like objects to an IPlug2 rectangle.
///
/// @param point Source top-left origin.
/// @param size Source width and height.
/// @return IPlug2 rectangle using `point` as origin and `size` as dimensions.
iplug::igraphics::IRECT to_irect(const usagi::concepts::geometry::point_concept auto &point,
                                 const usagi::concepts::geometry::size_concept auto &size) {
  return iplug::igraphics::IRECT::MakeXYWH(point.x(), point.y(), size.width(), size.height());
}

/// Converts a rectangle-like object to an IPlug2 rectangle.
///
/// @param rect Source left, top, right, and bottom edges.
/// @return IPlug2 rectangle with the same edges.
iplug::igraphics::IRECT to_irect(const usagi::concepts::geometry::rect_concept auto &rect) {
  auto [l, t, r, b] = rect();
  return iplug::igraphics::IRECT{l, t, r, b};
}
} // namespace usagi::wrapper::iplug2
