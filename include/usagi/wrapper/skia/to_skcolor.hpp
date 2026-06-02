#pragma once

#include <array>

#include <usagi/concepts/graphics/color_concept.hpp>

#include "include/core/SkColor.h"

namespace usagi::wrapper::skia {
/// Converts a floating-point usagi color to a Skia color.
///
/// @param c Source color with floating-point alpha, red, green, and blue channels.
/// @return Skia color using the source RGBA channel values.
SkColor to_skcolor(const usagi::concepts::graphics::float_color_concept auto &c) {
  return SkColor4f{c.red(), c.green(), c.blue(), c.alpha()}.toSkColor();
}

/// Converts an 8-bit usagi color to a Skia color.
///
/// @param c Source color with byte alpha, red, green, and blue channels.
/// @return Skia color using the source ARGB channel values.
SkColor to_skcolor(const usagi::concepts::graphics::byte_color_concept auto &c) {
  return SkColorSetARGB(c.alpha(), c.red(), c.green(), c.blue());
}
} // namespace usagi::wrapper::skia
