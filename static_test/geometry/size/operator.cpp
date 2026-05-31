#include <usagi/geometry/size/operator.hpp>

namespace {
static_assert([]() constexpr {
  constexpr usagi::geometry::size<float> s{4.f, 2.f};
  constexpr auto divided = s / 2.f;
  return divided.width() == 2.f && divided.height() == 1.f;
}());

static_assert([]() constexpr {
  constexpr usagi::geometry::size<float> s{4.f, 2.f};
  constexpr auto divided = 8.f / s;
  return divided.width() == 2.f && divided.height() == 4.f;
}());
} // namespace
