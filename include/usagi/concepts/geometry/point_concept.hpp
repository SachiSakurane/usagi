#pragma once

#include <usagi/concepts/arithmetic.hpp>

namespace usagi::concepts::geometry {
/**
 * pointが表現可能
 */
template <class PointType>
concept point_concept = requires(PointType &p) {
  requires usagi::utility::arithmetic<typename PointType::value_type>;

  { p.x() } -> usagi::utility::arithmetic;
  { p.y() } -> usagi::utility::arithmetic;
};
} // namespace usagi::concepts::geometry
