#pragma once

#include <type_traits>
#include <utility>

namespace usagi::concepts::ui {
/**
 * 描画可能か
 *
 * draw(DrawableType::draw_context_type& ) を持つ
 */
template <class DrawableType>
concept drawable = requires(DrawableType &d) {
  typename DrawableType::draw_context_type;
  typename DrawableType::offset_type;

  d.draw(std::declval<std::add_lvalue_reference_t<typename DrawableType::draw_context_type>>(),
         std::declval<typename DrawableType::offset_type>());
};
} // namespace usagi::concepts::ui
