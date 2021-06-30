#include <usagi/concepts/graphics/draw_contextable.h>

#include "../../mocks/draw_contextable.h"

namespace
{
  static_assert(usagi::concepts::graphics::draw_contextable<DrawContextable<float>>);
  static_assert(!usagi::concepts::graphics::draw_contextable<UnDrawContextable<float>>);
}
