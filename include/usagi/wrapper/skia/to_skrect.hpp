#pragma once

#include <usagi/concepts/geometry.hpp>

#include "include/core/SkRect.h"

namespace usagi::wrapper::skia {

SkRect to_skrect(const usagi::concepts::geometry::size_concept auto &size) {
  return SkRect::MakeWH(size.width(), size.height());
}

SkRect to_skrect(const usagi::concepts::geometry::point_concept auto &point,
                 const usagi::concepts::geometry::size_concept auto &size) {
  return SkRect::MakeXYWH(point.x(), point.y(), size.width(), size.height());
}

SkRect to_skrect(const usagi::concepts::geometry::rect_concept auto &rect) {
  auto [l, t, r, b] = rect();
  return SkRect::MakeLTRB(l, t, r, b);
}

} // namespace usagi::wrapper::skia
