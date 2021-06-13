#pragma once

#include <cassert>

#include <usagi/geometry/point.h>
#include <usagi/geometry/size.h>

namespace usagi
{
  template <class Type>
  struct rect
  {
  public:
    using value_type = Type;
    using size_type = size<value_type>;
    using point_type = point<value_type>;

    constexpr rect(value_type left, value_type top, value_type right, value_type bottom) : left{left}, top{top}, right(right), bottom{bottom}
    {
      assert(left <= right);
      assert(top <= bottom);
    }

    constexpr explicit rect(size_type size) : rect{point_type{.x = 0, .y = 0}, size}
    {
    }

    constexpr rect(point_type point, size_type size) : left{point.x}, top{point.y}, right(point.x + size.width), bottom{point.y + size.height}
    {
    }

    value_type l() const { return left; }
    value_type t() const { return top; }
    value_type r() const { return right; }
    value_type b() const { return bottom; }

    size_type size() const { return size_type{right - left, bottom - top}; }
    point_type center() const { return point_type{size() / static_cast<value_type>(2)}; }

  private:
    value_type left, top, right, bottom;
  };
}
