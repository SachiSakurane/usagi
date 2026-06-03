#pragma once

#include <cassert>
#include <cmath>
#include <type_traits>

#include <usagi/concepts/floating_point.hpp>
#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/concepts/geometry/transform_concept.hpp>
#include <usagi/geometry/point/operator.hpp>
#include <usagi/geometry/point/point.hpp>

namespace usagi::geometry {
namespace detail {
  template <usagi::concepts::floating_point ValueType>
  inline constexpr usagi::geometry::point<ValueType>
  rotate_transform_offset(const usagi::geometry::point<ValueType> &point, ValueType rotation) {
    if (rotation == static_cast<ValueType>(0)) {
      return point;
    }

    const auto sin = std::sin(rotation);
    const auto cos = std::cos(rotation);
    return usagi::geometry::point<ValueType>{point.x() * cos - point.y() * sin,
                                             point.x() * sin + point.y() * cos};
  }
} // namespace detail

/// Applies a transform to a point.
///
/// The point is scaled and rotated around `transform.origin()`, then translated
/// by `transform.translation()`.
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
  const auto transformed =
      detail::rotate_transform_offset((local - origin) * transform.scale(), transform.rotation());
  return transformed + origin + transform.translation();
}

/// Applies the inverse of a transform to a point.
///
/// This reverses `transform_point` for translation, rotation, scale, and origin.
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
  const auto local =
      detail::rotate_transform_offset(transformed - transform.translation() - origin,
                                      -transform.rotation());
  return local / scale + origin;
}
} // namespace usagi::geometry
