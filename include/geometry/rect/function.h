#pragma once

#include "rect.h"

namespace udon::components
{
  template <class Type>
  inline constexpr bool contain(const rect<Type> &r, const point<Type> &p)
  {
    return (r.l() <= p.x && p.x <= r.r()) && (r.t() <= p.y && p.y <= r.b());
  }
}
