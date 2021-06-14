#pragma once

#include <cmath>

#include <usagi/geometry/point/point.h>

namespace usagi
{
  template <class Type>
  inline constexpr decltype(auto) distance(const usagi::point<Type> &a, const usagi::point<Type> &b)
  {
    return typename usagi::variable_traits<Type>::variable_type{
        [a, b]()
        {
          auto x_sub = a.x() - b.x();
          auto y_sub = a.y() - b.y();
          return std::sqrt(x_sub * x_sub + y_sub * y_sub);
        }};
  }
}
