#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/rect/rect.hpp>
#include <usagi/geometry/size/size.hpp>
#include <usagi/geometry/transform/transform.hpp>

namespace usagi::geometry {
/// Bundles geometry types that share the same value type.
///
/// @tparam ValueType Arithmetic value type used by point, rect, size, and transform.
template <usagi::concepts::arithmetic ValueType>
struct geometry_traits {
  /// Shared geometry value type.
  using value_type = ValueType;
  /// Point type using `value_type`.
  using point_type = typename usagi::geometry::point<value_type>;
  /// Rectangle type using `value_type`.
  using rect_type = typename usagi::geometry::rect<value_type>;
  /// Size type using `value_type`.
  using size_type = typename usagi::geometry::size<value_type>;
  /// Transform type using `value_type`.
  using transform_type = typename usagi::geometry::transform<value_type>;
};
} // namespace usagi::geometry
