#pragma once

#include <usagi/geometry/rect/rect.hpp>
#include <usagi/graphics/color/color.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::concepts::graphics {
/**
 * 描画のために必要なモノを持っているか
 */
template <class DrawContextType>
concept draw_contextable = requires(DrawContextType &d) {
  typename DrawContextType::draw_type;

  d.draw(std::declval<typename DrawContextType::draw_type>());
};
} // namespace usagi::concepts::graphics
