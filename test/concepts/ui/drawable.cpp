#include <usagi/concepts/graphics/color_concept.h>
#include <usagi/concepts/ui/drawable.h>

#include "../../mocks/drawable.h"
#include "../../mocks/draw_contextable.h"

namespace
{
  static_assert(usagi::concepts::ui::drawable<Drawable<float, DrawContextable<float>>>);
  static_assert(!usagi::concepts::ui::drawable<UnDrawable<float, DrawContextable<float>>>);
}
