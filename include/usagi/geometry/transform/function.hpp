#pragma once

#include <cassert>
#include <type_traits>

#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/concepts/geometry/transform_concept.hpp>
#include <usagi/geometry/point/operator.hpp>
#include <usagi/geometry/point/point.hpp>

namespace usagi::geometry {
/// Applies a transform to a point.
///
/// The point is scaled around `transform.origin()`, then translated by
/// `transform.translation()`. Rotation is stored on the transform type but is not
/// applied by this helper yet.
///
/// @param transform Transform-like object to apply.
/// @param point Point-like object in local coordinates.
/// @return Point in transformed coordinates.
inline constexpr decltype(auto)
transform_point(const usagi::concepts::geometry::transform_concept auto &transform,
                const usagi::concepts::geometry::point_concept auto &point) {
  using value_type = typename std::remove_cvref_t<decltype(transform)>::value_type;
  using point_type = usagi::geometry::point<value_type>;

  const auto origin = transform.origin();
  const auto local = point_type{point.x(), point.y()};
  return (local - origin) * transform.scale() + origin + transform.translation();
}

/// Applies the inverse of a transform to a point.
///
/// This reverses `transform_point` for translation and scale. Rotation is stored
/// on the transform type but is not applied by this helper yet.
///
/// @param transform Transform-like object to invert.
/// @param point Point-like object in transformed coordinates.
/// @return Point in local coordinates.
inline constexpr decltype(auto)
inverse_transform_point(const usagi::concepts::geometry::transform_concept auto &transform,
                        const usagi::concepts::geometry::point_concept auto &point) {
  using value_type = typename std::remove_cvref_t<decltype(transform)>::value_type;
  using point_type = usagi::geometry::point<value_type>;

  const auto scale = transform.scale();
  assert(scale.x() != static_cast<value_type>(0));
  assert(scale.y() != static_cast<value_type>(0));

  const auto origin = transform.origin();
  const auto transformed = point_type{point.x(), point.y()};
  return (transformed - transform.translation() - origin) / scale + origin;
}
} // namespace usagi::geometry
