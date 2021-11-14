#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/concepts/geometry/size_concept.hpp>

namespace usagi::concepts::geometry {
/**
 * rectが表現可能
 */
template <class RectType>
concept rect_concept = requires(RectType &r) {
  requires usagi::concepts::arithmetic<typename RectType::value_type>;

  { r.l() } -> usagi::concepts::arithmetic;
  { r.t() } -> usagi::concepts::arithmetic;
  { r.r() } -> usagi::concepts::arithmetic;
  { r.b() } -> usagi::concepts::arithmetic;
  { r.size() } -> usagi::concepts::geometry::size_concept;
  { r.center() } -> usagi::concepts::geometry::point_concept;
};
} // namespace usagi::concepts::geometry
