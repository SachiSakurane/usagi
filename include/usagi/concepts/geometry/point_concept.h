#pragma once

#include <utility>

#include <usagi/utility/convertible_to.h>

namespace usagi::concepts::geometry
{
  /** 
   * pointが表現可能
  */
  template <class PointType>
  concept point_concept = requires(PointType &p)
  {
    typename PointType::value_type;

    { p.x() } -> usagi::utility::convertible_to<typename PointType::value_type>;
    { p.y() } -> usagi::utility::convertible_to<typename PointType::value_type>;
  };
}
