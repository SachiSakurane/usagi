#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/geometry/size/size.hpp>

namespace {
static_assert(usagi::concepts::geometry::size_concept<usagi::geometry::size<int>>);
static_assert(usagi::concepts::geometry::size_concept<usagi::geometry::variable_size<int>>);
} // namespace
