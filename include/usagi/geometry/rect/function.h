#pragma once

#include <usagi/geometry/rect/rect.h>

namespace usagi
{
  template <class Type>
  inline constexpr bool contain(const rect<Type> &r, const point<Type> &p)
  {
    return (r.l() <= p.x() && p.x() <= r.r()) && (r.t() <= p.y() && p.y() <= r.b());
  }
}
