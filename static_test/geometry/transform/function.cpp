#include <usagi/geometry/transform/function.hpp>
#include <usagi/geometry/transform/transform.hpp>

namespace {
static_assert([]() constexpr {
  constexpr auto transform =
      usagi::geometry::transform<float>{usagi::geometry::point<float>{10.f, 20.f}, 0.f,
                                        usagi::geometry::point<float>{2.f, 3.f},
                                        usagi::geometry::point<float>{5.f, 7.f}};
  constexpr auto local = usagi::geometry::point<float>{8.f, 9.f};
  constexpr auto transformed = usagi::geometry::transform_point(transform, local);

  if (transformed != usagi::geometry::point<float>{21.f, 33.f}) {
    return false;
  }

  return usagi::geometry::inverse_transform_point(transform, transformed) == local;
}());
} // namespace
