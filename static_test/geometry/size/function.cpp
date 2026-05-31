#include <usagi/geometry/size/function.hpp>
#include <usagi/geometry/size/size.hpp>

namespace {
static_assert([]() constexpr {
  constexpr usagi::geometry::size<float> s{2.f, 1.f};
  return usagi::geometry::aspect_ratio(s) == 2.f;
}());
} // namespace
