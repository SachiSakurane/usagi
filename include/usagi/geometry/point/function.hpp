#pragma once

#include <cmath>
#include <type_traits>

#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/variable/variable_traits.hpp>

namespace usagi::geometry
{
  template <
      usagi::concepts::geometry::point_concept PointTypeA,
      usagi::concepts::geometry::point_concept PointTypeB,
      class = std::enable_if_t<std::is_same_v<typename PointTypeA::value_type, typename PointTypeB::value_type>>>
  inline constexpr decltype(auto) distance(const PointTypeA &a, const PointTypeB &b)
  {
    return typename usagi::variable_traits<typename PointTypeA::value_type>::variable_type{
        [a, b]()
        {
          auto x_sub = a.x() - b.x();
          auto y_sub = a.y() - b.y();
          return std::sqrt(x_sub * x_sub + y_sub * y_sub);
        }};
  }
}
