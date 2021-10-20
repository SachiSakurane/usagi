#pragma once

#include <usagi/concepts/geometry.hpp>

namespace usagi::wrapper::iplug2 {
iplug::igraphics::IRECT to_irect(const usagi::concepts::geometry::size_concept auto &size) {
  return iplug::igraphics::IRECT::MakeXYWH(0, 0, size.width(), size.height());
}

iplug::igraphics::IRECT to_irect(const usagi::concepts::geometry::point_concept auto &point,
                                 const usagi::concepts::geometry::size_concept auto &size) {
  return iplug::igraphics::IRECT::MakeXYWH(point.x(), point.y(), size.width(), size.height());
}

iplug::igraphics::IRECT to_irect(const usagi::concepts::geometry::rect_concept auto &rect) {
  auto [l, t, r, b] = rect();
  return iplug::igraphics::IRECT{l, t, r, b};
}
} // namespace usagi::wrapper::iplug2
