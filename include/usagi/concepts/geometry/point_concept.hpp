#pragma once

#include <usagi/utility/arithmetic.hpp>

namespace usagi::concepts::geometry
{
  /** 
   * pointが表現可能
  */
  template <class PointType>
  concept point_concept = requires(PointType &p)
  {
    {
      p.x()
      } -> usagi::utility::arithmetic;
    {
      p.y()
      } -> usagi::utility::arithmetic;
  };
}
