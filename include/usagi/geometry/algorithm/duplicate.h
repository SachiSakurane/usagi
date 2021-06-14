#pragma once

namespace usagi
{
  template <class GeometryType>
  inline constexpr decltype(auto) duplicate(const GeometryType &x)
  {
    return x.duplicate();
  }
}
