#pragma once

#include <usagi/concepts/arithmetic.hpp>

namespace usagi::concepts::geometry {
/// Matches point-like types with arithmetic x and y accessors.
///
/// @tparam PointType Type to test.
template <class PointType>
concept point_concept = requires(PointType &p) {
  requires usagi::concepts::arithmetic<typename PointType::value_type>;

  { p.x() } -> usagi::concepts::arithmetic;
  { p.y() } -> usagi::concepts::arithmetic;
};
} // namespace usagi::concepts::geometry
