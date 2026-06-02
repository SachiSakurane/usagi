#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry/point_concept.hpp>

namespace usagi::concepts::geometry {
/// Matches transform-like types with translation, rotation, scale, and origin accessors.
///
/// @tparam TransformType Type to test.
template <class TransformType>
concept transform_concept = requires(TransformType &t) {
  typename TransformType::point_type;

  requires usagi::concepts::arithmetic<typename TransformType::value_type>;
  requires usagi::concepts::geometry::point_concept<typename TransformType::point_type>;

  { t.translation() } -> usagi::concepts::geometry::point_concept;
  { t.rotation() } -> usagi::concepts::arithmetic;
  { t.scale() } -> usagi::concepts::geometry::point_concept;
  { t.origin() } -> usagi::concepts::geometry::point_concept;
};
} // namespace usagi::concepts::geometry
