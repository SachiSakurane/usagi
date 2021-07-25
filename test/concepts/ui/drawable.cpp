#include <usagi/concepts/ui/drawable.hpp>

#include "../../mocks/draw_context.hpp"
#include "../../mocks/drawable.hpp"

namespace {
static_assert(usagi::concepts::ui::drawable<Drawable<float, DrawContext>>);
static_assert(!usagi::concepts::ui::drawable<UnDrawable<float, DrawContext>>);
} // namespace
