#pragma once

#include <type_traits>
#include <utility>

#include <usagi/concepts/graphics/draw_contextable.hpp>

namespace usagi::concepts::ui
{
  /** 
   * 描画可能か
   * draw_context_type は draw_context を満たす 
  */
  template <class DrawableType>
  concept drawable =
      usagi::concepts::graphics::draw_contextable<typename DrawableType::draw_context_type> &&
      requires(DrawableType &d)
  {
    typename DrawableType::draw_context_type;

    d.draw(std::declval<std::add_lvalue_reference_t<typename DrawableType::draw_context_type>>());
  };
}
