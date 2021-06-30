#pragma once

#include <usagi/utility/arithmetic.h>

namespace usagi::concepts::graphics
{
  /** 
   * colorが表現可能
  */
  template <class ColorType>
  concept color_concept = requires(ColorType &c)
  {
    typename ColorType::value_type;

    { c.r() } -> usagi::utility::arithmetic;
    { c.g() } -> usagi::utility::arithmetic;
    { c.b() } -> usagi::utility::arithmetic;
    { c.a() } -> usagi::utility::arithmetic;
  };
}
