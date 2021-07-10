#include <usagi/concepts/graphics/color_concept.hpp>
#include <usagi/concepts/ui/drawable.hpp>

#include "../../mocks/draw_contextable.hpp"
#include "../../mocks/drawable.hpp"

namespace {
static_assert(usagi::concepts::ui::drawable<Drawable<float, DrawContextable>>);
static_assert(!usagi::concepts::ui::drawable<UnDrawable<float, DrawContextable>>);
} // namespace
