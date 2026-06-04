#pragma once

#include <type_traits>
#include <utility>

#include <usagi/concepts/floating_point.hpp>
#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/concepts/geometry/transform_concept.hpp>
#include <usagi/geometry/point/operator.hpp>
#include <usagi/math/constants.hpp>
#include <usagi/ui/draw_transform.hpp>

#include "include/core/SkCanvas.h"

namespace usagi::ui {
namespace detail {
  template <usagi::concepts::floating_point ValueType>
  inline constexpr ValueType radians_to_degrees(ValueType radians) {
    constexpr auto half_turn = static_cast<ValueType>(180);
    return radians * half_turn / usagi::math::pi<ValueType>;
  }
} // namespace detail

/// Skia draw transform adapter.
///
/// Applies scale and rotation around `offset + transform.origin()` using Skia's
/// `save`, `translate`, `rotate`, `scale`, and `restore` calls. Translation
/// remains represented by the existing draw offset.
template <>
struct draw_transform_traits<SkCanvas> {
  /// Draws with a usagi transform applied to a Skia canvas.
  ///
  /// @param canvas Skia canvas to transform for the duration of `draw`.
  /// @param transform Transform to apply.
  /// @param offset Current accumulated draw offset.
  /// @param draw Callable that performs the actual draw operation.
  static void draw(SkCanvas &canvas,
                   const usagi::concepts::geometry::transform_concept auto &transform,
                   const usagi::concepts::geometry::point_concept auto &offset, auto &&draw) {
    using value_type = typename std::remove_cvref_t<decltype(transform)>::value_type;

    const auto scale = transform.scale();
    const auto rotation = transform.rotation();
    const auto is_identity = scale.x() == static_cast<value_type>(1) &&
        scale.y() == static_cast<value_type>(1) && rotation == static_cast<value_type>(0);

    if (is_identity) {
      std::forward<decltype(draw)>(draw)();
      return;
    }

    const auto origin = offset + transform.origin();
    canvas.save();
    canvas.translate(origin.x(), origin.y());
    canvas.rotate(detail::radians_to_degrees(rotation));
    canvas.scale(scale.x(), scale.y());
    canvas.translate(-origin.x(), -origin.y());
    std::forward<decltype(draw)>(draw)();
    canvas.restore();
  }
};
} // namespace usagi::ui
