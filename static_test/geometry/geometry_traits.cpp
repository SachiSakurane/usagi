#include <type_traits>

#include <usagi/geometry/geometry_traits.hpp>

namespace {
using traits = usagi::geometry::geometry_traits<float>;

static_assert(std::is_same_v<traits::value_type, float>);
static_assert(std::is_same_v<traits::point_type, usagi::geometry::point<float>>);
static_assert(std::is_same_v<traits::rect_type, usagi::geometry::rect<float>>);
static_assert(std::is_same_v<traits::size_type, usagi::geometry::size<float>>);
} // namespace
