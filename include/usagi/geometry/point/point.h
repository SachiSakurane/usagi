#pragma once

#include <usagi/geometry/size/size.h>

namespace usagi
{
  template <class Type>
  struct point
  {
    using value_type = Type;
    value_type x, y;

    point() = default;
    explicit point(size<value_type> s) : x{s.width}, y{s.height} {}
  };
}
