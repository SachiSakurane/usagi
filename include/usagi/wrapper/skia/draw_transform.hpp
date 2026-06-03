#pragma once

#include <type_traits>
#include <utility>

#include <usagi/concepts/floating_point.hpp>
#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/concepts/geometry/transform_concept.hpp>
#include <usagi/geometry/point/operator.hpp>

#include "include/core/SkCanvas.h"

namespace usagi::wrapper::skia {
namespace detail {
  template <usagi::concepts::floating_point ValueType>
  inline constexpr ValueType radians_to_degrees(ValueType radians) {
    constexpr auto half_turn = static_cast<ValueType>(180);
    constexpr auto pi = static_cast<ValueType>(3.14159265358979323846);
    return radians * half_turn / pi;
  }
} // namespace detail

/// Draws with a usagi transform applied to a Skia canvas.
///
/// This applies scale and rotation around `offset + transform.origin()` using
/// Skia's `save`, `translate`, `rotate`, `scale`, and `restore` calls, then
/// invokes `draw`. Translation remains represented by the existing draw offset.
///
/// @param canvas Skia canvas to transform for the duration of `draw`.
/// @param transform Transform to apply.
/// @param offset Current accumulated draw offset.
/// @param draw Callable that performs the actual draw operation.
template <class FunctionType>
void draw_with_transform(SkCanvas &canvas,
                         const usagi::concepts::geometry::transform_concept auto &transform,
                         const usagi::concepts::geometry::point_concept auto &offset,
                         FunctionType &&draw) {
  using value_type = typename std::remove_cvref_t<decltype(transform)>::value_type;

  const auto scale = transform.scale();
  const auto rotation = transform.rotation();
  const auto is_identity = scale.x() == static_cast<value_type>(1) &&
      scale.y() == static_cast<value_type>(1) && rotation == static_cast<value_type>(0);

  if (is_identity) {
    std::forward<FunctionType>(draw)();
    return;
  }

  const auto origin = offset + transform.origin();
  canvas.save();
  canvas.translate(origin.x(), origin.y());
  canvas.rotate(detail::radians_to_degrees(rotation));
  canvas.scale(scale.x(), scale.y());
  canvas.translate(-origin.x(), -origin.y());
  std::forward<FunctionType>(draw)();
  canvas.restore();
}
} // namespace usagi::wrapper::skia
