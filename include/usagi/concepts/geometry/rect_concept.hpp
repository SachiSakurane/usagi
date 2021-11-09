#pragma once

#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::concepts::geometry {
/**
 * rectが表現可能
 */
template <class RectType>
concept rect_concept = requires(RectType &r) {
  requires usagi::utility::arithmetic<typename RectType::value_type>;

  { r.l() } -> usagi::utility::arithmetic;
  { r.t() } -> usagi::utility::arithmetic;
  { r.r() } -> usagi::utility::arithmetic;
  { r.b() } -> usagi::utility::arithmetic;
  { r.size() } -> usagi::concepts::geometry::size_concept;
  { r.center() } -> usagi::concepts::geometry::point_concept;
};
} // namespace usagi::concepts::geometry
