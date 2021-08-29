#pragma once

#include <usagi/concepts/geometry.hpp>

namespace usagi::wrapper::skia {

template <usagi::concepts::geometry::size_concept SizeType>
SkRect to_rect(const SizeType &size) {
  return SkRect::MakeWH(size.width(), size.height());
}

template <usagi::concepts::geometry::point_concept PointType,
          usagi::concepts::geometry::size_concept SizeType>
SkRect to_rect(const PointType &point, const SizeType &size) {
  return SkRect::MakeXYWH(point.x(), point.y(), size.width(), size.height());
}

template <usagi::concepts::geometry::rect_concept RectType>
SkRect to_rect(const RectType &rect) {
  auto [l, t, r, b] = std::forward<RectType>(rect)();
  return SkRect::MakeLTRB(l, t, r, b);
}

} // namespace usagi::wrapper::skia
