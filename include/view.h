#pragma once

#include <vector>

#include "geometry/rect.h"

// アンカーが欲しい
// アプリをunfoldした時に真ん中にしたいので
namespace udon::components
{
  struct view
  {
  public:
    void on_down(const components::point<float> &p) {}
    void on_drag(const components::point<float> &p) {}
    void on_up(const components::point<float> &p) {}
    void on_cancel(const components::point<float> &p) {}
  };
}
