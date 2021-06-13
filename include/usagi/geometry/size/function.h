#pragma once

#include <usagi/geometry/size/size.h>

namespace usagi
{
  template <class Type>
  inline constexpr decltype(auto) duplicate(const usagi::size<Type> x)
  {
    return x.duplicate();
  }
}
