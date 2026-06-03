#include <usagi/geometry/transform/function.hpp>
#include <usagi/geometry/transform/transform.hpp>

namespace {
static_assert([]() constexpr {
  constexpr auto transform =
      usagi::geometry::transform<int>{usagi::geometry::point<int>{10, 20}, 0,
                                      usagi::geometry::point<int>{2, 3},
                                      usagi::geometry::point<int>{5, 7}};
  constexpr auto local = usagi::geometry::point<int>{8, 9};
  constexpr auto transformed = usagi::geometry::transform_point(transform, local);

  if (transformed != usagi::geometry::point<int>{21, 33}) {
    return false;
  }

  return usagi::geometry::inverse_transform_point(transform, transformed) == local;
}());
} // namespace
