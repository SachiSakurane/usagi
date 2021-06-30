#pragma once

#include <usagi/graphics/color/color.h>
#include <usagi/utility/arithmetic.h>

namespace usagi::concepts::graphics
{
  /** 
   * 描画のために必要なモノを持っているか
  */
  template <class DrawContextType>
  concept draw_contextable = requires(DrawContextType &d)
  {
    // size とは若干意味が異なるのであえて直書きしている
    { d.width() } -> usagi::utility::arithmetic;
    { d.height() } -> usagi::utility::arithmetic;

    d.fill(std::declval<usagi::graphics::color<int>>());
    d.fill(std::declval<usagi::graphics::color<float>>());
  };
}
