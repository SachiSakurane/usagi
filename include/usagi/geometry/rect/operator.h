#pragma once

#include <usagi/geometry/rect/rect.h>

namespace usagi
{
  template <class Type>
  inline constexpr bool operator==(const usagi::rect<Type> &lhs, const usagi::rect<Type> &rhs)
  {
    return lhs.l() == rhs.l() && lhs.r() == rhs.r() && lhs.t() == rhs.t() && lhs.b() == rhs.b();
  }

  template <class Type>
  inline constexpr bool operator!=(const usagi::rect<Type> &lhs, const usagi::rect<Type> &rhs)
  {
    return !(lhs == rhs);
  }

  template <class Type>
  inline constexpr decltype(auto) operator+(const usagi::rect<Type> &lhs, const usagi::point<Type> &rhs)
  {
    return usagi::rect<Type>{
        [lhs, rhs]()
        { return lhs.l() + rhs.x(); },
        [lhs, rhs]()
        { return lhs.t() + rhs.y(); },
        [lhs, rhs]()
        { return lhs.r() + rhs.x(); },
        [lhs, rhs]()
        { return lhs.b() + rhs.y(); }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator-(const rect<Type> &lhs, const point<Type> &rhs)
  {
    return usagi::rect<Type>{
        [lhs, rhs]()
        { return lhs.l() - rhs.x(); },
        [lhs, rhs]()
        { return lhs.t() - rhs.y(); },
        [lhs, rhs]()
        { return lhs.r() - rhs.x(); },
        [lhs, rhs]()
        { return lhs.b() - rhs.y(); }};
  }
}
