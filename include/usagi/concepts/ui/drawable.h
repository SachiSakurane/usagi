#pragma once

#include <type_traits>
#include <utility>

namespace usagi::concepts::ui
{
  /** 
   * 描画可能か
   * draw_type は draw_context を満たす 
  */
  template <class DrawableType>
  concept drawable = requires(DrawableType& d)
  {
    typename DrawableType::draw_type;

    d.draw(std::declval<std::add_lvalue_reference_t<typename DrawableType::draw_type>>());
  };
}
