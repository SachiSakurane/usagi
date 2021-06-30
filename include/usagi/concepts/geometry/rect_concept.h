#pragma once

#include <usagi/concepts/geometry/point_concept.h>
#include <usagi/concepts/geometry/size_concept.h>
#include <usagi/utility/arithmetic.h>

namespace usagi::concepts::geometry
{
  /** 
   * rectが表現可能
  */
  template <class RectType>
  concept rect_concept = requires(RectType &r)
  {
    { r.l() } -> usagi::utility::arithmetic;
    { r.t() } -> usagi::utility::arithmetic;
    { r.r() } -> usagi::utility::arithmetic;
    { r.b() } -> usagi::utility::arithmetic;
    { r.size() } -> usagi::concepts::geometry::size_concept;
    { r.center() } -> usagi::concepts::geometry::point_concept;
  };
}
