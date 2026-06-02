#pragma once

#include <array>

#include <usagi/concepts/graphics/color_concept.hpp>

namespace usagi::wrapper::iplug2 {
/// Converts a floating-point usagi color to an IPlug2 `IColor`.
///
/// @param c Source color with floating-point alpha, red, green, and blue channels.
/// @return IPlug2 color using the source RGBA channel values.
iplug::igraphics::IColor to_icolor(const usagi::concepts::graphics::float_color_concept auto &c) {
  std::array<float, 4> tmp{static_cast<float>(c.red()), static_cast<float>(c.green()),
                           static_cast<float>(c.blue()), static_cast<float>(c.alpha())};
  return iplug::igraphics::IColor::FromRGBAf(tmp.data());
}
} // namespace usagi::wrapper::iplug2
