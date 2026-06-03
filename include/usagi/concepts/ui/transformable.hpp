#pragma once

#include <utility>

#include <usagi/concepts/floating_point.hpp>
#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/concepts/geometry/transform_concept.hpp>

namespace usagi::concepts::ui {
/// Matches view-like types that expose layout-after transform controls.
///
/// @tparam TransformableType Type to test.
template <class TransformableType>
concept transformable = requires(TransformableType &t) {
  typename TransformableType::value_type;
  typename TransformableType::point_type;
  typename TransformableType::transform_type;

  requires usagi::concepts::floating_point<typename TransformableType::value_type>;
  requires usagi::concepts::geometry::point_concept<typename TransformableType::point_type>;
  requires usagi::concepts::geometry::transform_concept<
      typename TransformableType::transform_type>;

  { t.transform() } -> usagi::concepts::geometry::transform_concept;
  t.set_transform(std::declval<typename TransformableType::transform_type>());

  { t.translation() } -> usagi::concepts::geometry::point_concept;
  t.set_translation(std::declval<typename TransformableType::point_type>());

  { t.rotation() } -> usagi::concepts::floating_point;
  t.set_rotation(std::declval<typename TransformableType::value_type>());

  { t.scale() } -> usagi::concepts::geometry::point_concept;
  t.set_scale(std::declval<typename TransformableType::point_type>());
  t.set_scale(std::declval<typename TransformableType::point_type>(),
              std::declval<typename TransformableType::point_type>());
};
} // namespace usagi::concepts::ui
