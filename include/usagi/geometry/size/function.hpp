#pragma once

#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/geometry/size/size.hpp>

namespace usagi::geometry {
template <usagi::concepts::geometry::float_size_concept SizeType>
inline constexpr decltype(auto) aspect_ratio(const SizeType &size) {
  return size.width() / size.height();
}
} // namespace usagi::geometry
