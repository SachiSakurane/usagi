#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/geometry/rect/rect.hpp>

namespace {
static_assert(usagi::concepts::geometry::rect_concept<usagi::geometry::rect<int>>);
static_assert(usagi::concepts::geometry::rect_concept<usagi::geometry::variable_rect<int>>);
}
