#include <usagi/geometry/rect/operator.hpp>

namespace {
static_assert([]() constexpr {
  constexpr usagi::geometry::rect<float> lhs{2.f, 4.f, 42.f, 24.f};
  constexpr usagi::geometry::rect<float> rhs{3.f, 4.f, 42.f, 24.f};
  return lhs == lhs && lhs != rhs;
}());

static_assert([]() constexpr {
  constexpr usagi::geometry::rect<float> r{2.f, 4.f, 42.f, 24.f};
  constexpr usagi::geometry::point<float> offset{3.f, 5.f};
  constexpr auto moved = r + offset;
  constexpr auto restored = moved - offset;
  return moved.l() == 5.f && moved.t() == 9.f && moved.r() == 45.f && moved.b() == 29.f &&
      restored == r;
}());
} // namespace
