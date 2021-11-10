#include <usagi/concepts/graphics/color_concept.hpp>
#include <usagi/graphics/color/color.hpp>

namespace {
static_assert(usagi::concepts::graphics::basic_color_concept<usagi::graphics::basic_color<int>>);
static_assert(usagi::concepts::graphics::basic_color_concept<usagi::graphics::variable_color<int>>);
} // namespace
