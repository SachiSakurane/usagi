#pragma once

#include <utility>

#include <usagi/utility/convertible_to.h>

namespace usagi::concepts::graphics
{
  /** 
   * colorが表現可能
  */
  template <class ColorType>
  concept color_concept = requires(ColorType &c)
  {
    typename ColorType::value_type;

    { c.r() } -> usagi::utility::convertible_to<typename ColorType::value_type>;
    { c.g() } -> usagi::utility::convertible_to<typename ColorType::value_type>;
    { c.b() } -> usagi::utility::convertible_to<typename ColorType::value_type>;
    { c.a() } -> usagi::utility::convertible_to<typename ColorType::value_type>;
  };
}
