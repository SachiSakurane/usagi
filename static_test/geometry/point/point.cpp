#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/geometry/point/point.hpp>

namespace {
static_assert(usagi::concepts::geometry::point_concept<usagi::geometry::point<int>>);
static_assert(usagi::concepts::geometry::point_concept<usagi::geometry::variable_point<int>>);
} // namespace
