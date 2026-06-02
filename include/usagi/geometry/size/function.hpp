#pragma once

#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/geometry/detail/assert.hpp>
#include <usagi/geometry/size/size.hpp>

namespace usagi::geometry {
/// Returns the width-to-height ratio for a floating-point size.
///
/// @param size Size-like input whose width is divided by its height.
/// @return `size.width() / size.height()`.
/// @pre `size.height()` must be non-zero.
template <usagi::concepts::geometry::float_size_concept SizeType>
inline constexpr decltype(auto) aspect_ratio(const SizeType &size) {
  detail::assert_nonzero_divisor(size.height());
  return size.width() / size.height();
}
} // namespace usagi::geometry
