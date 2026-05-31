#include <usagi/geometry/point/operator.hpp>

namespace {
static_assert([]() constexpr {
  constexpr usagi::geometry::point<float> lhs{2.f, 4.f};
  constexpr usagi::geometry::point<float> rhs{3.f, 5.f};
  return lhs == lhs && lhs != rhs;
}());

static_assert([]() constexpr {
  constexpr usagi::geometry::point<float> lhs{2.f, 4.f};
  constexpr usagi::geometry::point<float> rhs{3.f, 5.f};
  constexpr auto sum = lhs + rhs;
  constexpr auto diff = rhs - lhs;
  constexpr auto scaled = lhs * 2.f;
  constexpr auto divided = rhs / usagi::geometry::point<float>{3.f, 5.f};
  return sum.x() == 5.f && sum.y() == 9.f && diff.x() == 1.f && diff.y() == 1.f &&
      scaled.x() == 4.f && scaled.y() == 8.f && divided.x() == 1.f && divided.y() == 1.f;
}());
} // namespace
