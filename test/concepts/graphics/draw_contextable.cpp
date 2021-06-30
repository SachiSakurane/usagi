#include <usagi/concepts/graphics/draw_contextable.hpp>

#include "../../mocks/draw_contextable.hpp"

namespace
{
  static_assert(usagi::concepts::graphics::draw_contextable<DrawContextable<float>>);
  static_assert(!usagi::concepts::graphics::draw_contextable<UnDrawContextable<float>>);
}
