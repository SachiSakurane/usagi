#include <usagi/geometry/rect/function.hpp>

namespace {
static_assert([]() constexpr {
  constexpr usagi::geometry::point<float> center{22.f, 14.f};
  constexpr usagi::geometry::size<float> size{40.f, 20.f};
  constexpr auto r = usagi::geometry::make_from_center(center, size);
  return r.l() == 2.f && r.t() == 4.f && r.r() == 42.f && r.b() == 24.f;
}());

static_assert([]() constexpr {
  constexpr usagi::geometry::rect<float> r{2.f, 4.f, 42.f, 24.f};
  constexpr auto moved = usagi::geometry::transform(r, 3.f, 5.f);
  return moved.l() == 5.f && moved.t() == 9.f && moved.r() == 45.f && moved.b() == 29.f;
}());

static_assert([]() constexpr {
  constexpr usagi::geometry::rect<float> r{2.f, 4.f, 42.f, 24.f};
  constexpr auto left = usagi::geometry::from_left(r, 10.f);
  constexpr auto top = usagi::geometry::from_top(r, 10.f);
  constexpr auto right = usagi::geometry::from_right(r, 10.f);
  constexpr auto bottom = usagi::geometry::from_bottom(r, 10.f);
  return left.r() == 12.f && top.b() == 14.f && right.l() == 32.f && bottom.t() == 14.f;
}());

static_assert([]() constexpr {
  constexpr usagi::geometry::rect<float> r{2.f, 4.f, 42.f, 24.f};
  constexpr auto width = usagi::geometry::from_width(r, 10.f);
  constexpr auto height = usagi::geometry::from_height(r, 8.f);
  constexpr auto size = usagi::geometry::from_size(r, 10.f, 8.f);
  return width.l() == 17.f && width.r() == 27.f && height.t() == 10.f &&
      height.b() == 18.f && size.l() == 17.f && size.t() == 10.f && size.r() == 27.f &&
      size.b() == 18.f;
}());

static_assert([]() constexpr {
  constexpr usagi::geometry::rect<float> r{0.f, 0.f, 42.f, 42.f};
  constexpr auto left_pair = usagi::geometry::reduce_from_left(r, 10.f);
  constexpr auto bottom_pair = usagi::geometry::reduce_from_bottom(r, 12.f);
  constexpr auto left = std::get<0>(left_pair);
  constexpr auto right = std::get<1>(left_pair);
  constexpr auto bottom = std::get<0>(bottom_pair);
  constexpr auto top = std::get<1>(bottom_pair);
  return left.r() == 10.f && right.l() == 10.f && bottom.t() == 30.f && top.b() == 30.f;
}());

static_assert([]() constexpr {
  constexpr usagi::geometry::rect<float> r{0.f, 0.f, 42.f, 42.f};
  constexpr usagi::geometry::point<float> inside{42.f, 42.f};
  constexpr usagi::geometry::point<float> outside{43.f, 42.f};
  return usagi::geometry::contain(r, inside) && !usagi::geometry::contain(r, outside);
}());

static_assert([]() constexpr {
  constexpr usagi::geometry::rect<float> r{0.f, 0.f, 42.f, 42.f};
  constexpr auto all = usagi::geometry::padding(r, 16.f);
  constexpr auto axis = usagi::geometry::padding(r, 4.f, 8.f);
  constexpr auto vertical = usagi::geometry::padding_height(r, 30.f);
  return all.l() == 16.f && all.t() == 16.f && all.r() == 26.f && all.b() == 26.f &&
      axis.l() == 8.f && axis.t() == 4.f && axis.r() == 34.f && axis.b() == 38.f &&
      vertical.t() == 21.f && vertical.b() == 21.f;
}());
} // namespace
