#pragma once

#include <type_traits>
#include <utility>

#include <usagi/concepts/geometry/rect_concept.h>
#include <usagi/concepts/graphics/draw_contextable.h>

namespace usagi::concepts::ui
{
  /** 
   * 描画可能か
   * draw_context_type は draw_context を満たす 
  */
  template <class DrawableType>
  concept drawable =
      usagi::concepts::geometry::rect_concept<typename DrawableType::rect_type> &&
      usagi::concepts::graphics::draw_contextable<typename DrawableType::draw_context_type> &&
      requires(DrawableType &d)
  {
    typename DrawableType::draw_context_type;
    typename DrawableType::rect_type;

    d.draw(
        std::declval<typename DrawableType::rect_type>(),
        std::declval<std::add_lvalue_reference_t<typename DrawableType::draw_context_type>>());
  };
}
