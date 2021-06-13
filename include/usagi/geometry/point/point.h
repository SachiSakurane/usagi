#pragma once

#include <usagi/geometry/size/size.h>

namespace usagi
{
  template <class Type>
  struct point
  {
    using value_type = typename usagi::variable_traits<Type>::value_type;
    using variable_type = typename usagi::variable_traits<Type>::variable_type;

    point() : x_{}, y_{} {}
    point(const usagi::size<variable_type> &s) : x_{[s]()
                                                    { return s.width(); }},
                                                 y_{[s]()
                                                    { return s.height(); }} {}
    point(variable_type x, variable_type y) : x_{x}, y_{y} {}

    decltype(auto) x() const { return x_(); }
    decltype(auto) y() const { return y_(); }

    decltype(auto) duplicate() const { return point<Type>{x(), y()}; }

  private:
    variable_type x_, y_;
  };
}
