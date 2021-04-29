#pragma once

#include <cassert>

#include "../point.h"

namespace udon::components
{
  template <class Type>
  struct rect
  {
  public:
    constexpr rect(Type left, Type top, Type right, Type bottom) : left{left}, top{top}, right(right), bottom{bottom}
    {
      assert(left <= right);
      assert(top <= bottom);
    }

    constexpr rect(Type width, Type height) : rect{point<Type>{.x = 0, .y = 0}, width, height}
    {
    }

    constexpr rect(point<Type> point, Type width, Type height) : left{point.x}, top{point.y}, right(point.x + width), bottom{point.y + height}
    {
      assert(width >= 0);
      assert(height >= 0);
    }

    Type l() const { return left; }
    Type t() const { return top; }
    Type r() const { return right; }
    Type b() const { return bottom; }

    Type width() const { return right - left; }
    Type height() const { return bottom - top; }

    Type center_x() const { return width() / static_cast<Type>(2); }
    Type center_y() const { return height() / static_cast<Type>(2); }

    point<Type> center() const { return point<Type>{center_x(), center_y()}; }

  private:
    Type left, top, right, bottom;
  };
}
