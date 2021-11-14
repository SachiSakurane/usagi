#pragma once

#include <usagi/concepts/arithmetic.hpp>

namespace usagi::concepts::geometry {
/**
 * pointが表現可能
 */
template <class PointType>
concept point_concept = requires(PointType &p) {
  requires usagi::concepts::arithmetic<typename PointType::value_type>;

  { p.x() } -> usagi::concepts::arithmetic;
  { p.y() } -> usagi::concepts::arithmetic;
};
} // namespace usagi::concepts::geometry
