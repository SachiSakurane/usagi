#pragma once

#include <utility>

#include <usagi/concepts/geometry/point_concept.h>
#include <usagi/concepts/geometry/size_concept.h>
#include <usagi/utility/convertible_to.h>

namespace usagi::concepts::geometry
{
  /** 
   * rectが表現可能
  */
  template <class RectType>
  concept rect_concept = requires(RectType &r)
  {
    typename RectType::value_type;

    { r.l() } -> usagi::utility::convertible_to<typename RectType::value_type>;
    { r.t() } -> usagi::utility::convertible_to<typename RectType::value_type>;
    { r.r() } -> usagi::utility::convertible_to<typename RectType::value_type>;
    { r.b() } -> usagi::utility::convertible_to<typename RectType::value_type>;
    { r.size() } -> usagi::concepts::geometry::size_concept;
    { r.center() } -> usagi::concepts::geometry::point_concept;
  };
}
