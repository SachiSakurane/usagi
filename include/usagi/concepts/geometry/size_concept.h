#pragma once

#include <usagi/utility/arithmetic.h>

namespace usagi::concepts::geometry
{
  /** 
   * sizeが表現可能
  */
  template <class SizeType>
  concept size_concept = requires(SizeType &s)
  {
    { s.width() } -> usagi::utility::arithmetic;
    { s.height() } -> usagi::utility::arithmetic;
  };
}
