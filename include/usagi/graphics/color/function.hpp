#pragma once

#include <concepts>

#include <usagi/concepts/graphics/color_concept.hpp>

namespace usagi::graphics {
/// Returns a byte color with alpha scaled by a floating-point multiplier.
///
/// @param c Source byte color.
/// @param alpha Multiplier applied to the source alpha channel.
/// @return Color of the same concrete type as `c` with scaled alpha and unchanged RGB channels.
template <std::floating_point FloatType>
inline constexpr decltype(auto)
with_alpha(const usagi::concepts::graphics::byte_color_concept auto &c, FloatType alpha) {
  using value_type = decltype(c.red());
  return std::remove_cvref_t<decltype(c)>{static_cast<value_type>(c.alpha() * alpha), c.red(),
                                          c.green(), c.blue()};
}
} // namespace usagi::graphics
