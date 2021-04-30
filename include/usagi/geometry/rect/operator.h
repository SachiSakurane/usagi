#pragma once

#include <usagi/geometry/rect/rect.h>

namespace usagi
{
  template <class Type>
  inline constexpr decltype(auto) operator+(const rect<Type> &lhs, const point<Type> &rhs)
  {
    return rect<Type>{
        lhs.l() + rhs.x,
        lhs.t() + rhs.y,
        lhs.r() + rhs.x,
        lhs.b() + rhs.y};
  }

  template <class Type>
  inline constexpr decltype(auto) operator-(const rect<Type> &lhs, const point<Type> &rhs)
  {
    return rect<Type>{
        lhs.l() - rhs.x,
        lhs.t() - rhs.y,
        lhs.r() - rhs.x,
        lhs.b() - rhs.y};
  }
}
