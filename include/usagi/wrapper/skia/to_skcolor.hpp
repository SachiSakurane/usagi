#pragma once

#include <array>

#include <usagi/concepts/graphics/color_concept.hpp>

#include "SkColor.h"

namespace usagi::wrapper::skia {
SkColor to_skcolor(const usagi::concepts::graphics::float_color_concept auto &c) {
  return SkColor4f{c.red(), c.green(), c.blue(), c.alpha()}.toSkColor();
}
} // namespace usagi::wrapper::skia

