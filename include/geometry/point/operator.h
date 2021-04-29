#pragma once

#include "point.h"

namespace udon::components
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