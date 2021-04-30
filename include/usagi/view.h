#pragma once

#include <vector>

#include <usagi/geometry/rect.h>

// アンカーが欲しい
// アプリをunfoldした時に真ん中にしたいので
namespace usagi
{
  struct view
  {
  public:
    void on_down(const point<float> &p) {}
    void on_drag(const point<float> &p) {}
    void on_up(const point<float> &p) {}
    void on_cancel(const point<float> &p) {}
  };
}
