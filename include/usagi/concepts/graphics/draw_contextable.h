#pragma once

#include <utility>

#include <usagi/graphics/color/color.h>

namespace usagi::concepts::graphics
{
  /** 
   * 描画のために必要なモノを持っているか
  */
  template <class DrawContextType>
  concept draw_contextable = requires(DrawContextType &d)
  {
    d.fill(std::declval<usagi::graphics::color<int>>());
    d.fill(std::declval<usagi::graphics::color<float>>());
  };
}
