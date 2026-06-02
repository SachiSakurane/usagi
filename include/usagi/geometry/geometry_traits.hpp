#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/rect/rect.hpp>
#include <usagi/geometry/size/size.hpp>

namespace usagi::geometry {
/// Bundles geometry types that share the same value type.
///
/// @tparam ValueType Arithmetic value type used by point, rect, and size.
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
};
} // namespace usagi::geometry
