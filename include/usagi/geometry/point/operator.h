#pragma once

#include <usagi/geometry/point/point.h>

namespace usagi
{
  template <class Type>
  inline constexpr decltype(auto) operator+(const point<Type> &lhs, const point<Type> &rhs)
  {
    return point<Type>{.x = lhs.x + rhs.x, .y = lhs.y + rhs.y};
  }

  template <class Type>
  inline constexpr decltype(auto) operator-(const point<Type> &lhs, const point<Type> &rhs)
  {
    return point<Type>{.x = lhs.x - rhs.x, .y = lhs.y - rhs.y};
  }
}