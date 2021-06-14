#pragma once

#include <usagi/geometry/size/size.h>

namespace usagi
{
  template <class Type>
  struct point
  {
    using value_type = typename usagi::variable_traits<Type>::value_type;
    using variable_type = typename usagi::variable_traits<Type>::variable_type;

    constexpr point() : x_{}, y_{} {}
    constexpr explicit point(const usagi::size<Type> &s) : x_{[s]()
                                                              { return s.width(); }},
                                                           y_{[s]()
                                                              { return s.height(); }} {}
    constexpr point(variable_type x, variable_type y) : x_{x}, y_{y} {}

    value_type x() const { return x_(); }
    value_type y() const { return y_(); }

    point<value_type> duplicate() const { return point<value_type>{x(), y()}; }

  private:
    variable_type x_, y_;
  };
}
