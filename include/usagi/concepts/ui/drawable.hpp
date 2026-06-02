#pragma once

#include <type_traits>
#include <utility>

namespace usagi::concepts::ui {
/// Matches types that can draw with a draw context and offset.
///
/// @tparam DrawableType Type to test.
template <class DrawableType>
concept drawable = requires(DrawableType &d) {
  typename DrawableType::draw_context_type;
  typename DrawableType::offset_type;

  d.draw(std::declval<std::add_lvalue_reference_t<typename DrawableType::draw_context_type>>(),
         std::declval<typename DrawableType::offset_type>());
};
} // namespace usagi::concepts::ui
