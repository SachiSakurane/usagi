#pragma once

#include <utility>

namespace usagi::concepts::graphics
{
  /** 
   * 描画のために必要なモノを持っているか
  */
  template <class DrawContextType>
  concept draw_contextable = requires(DrawContextType &d)
  {
    d.fill();
  };
}
