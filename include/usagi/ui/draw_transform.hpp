#pragma once

#include <type_traits>
#include <utility>

#include <usagi/concepts/floating_point.hpp>
#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/concepts/geometry/transform_concept.hpp>
#include <usagi/geometry/point/operator.hpp>

namespace usagi::ui {
namespace detail {
  template <class DrawContextType, class ValueType>
  concept draw_transform_context = requires(DrawContextType &context, ValueType value) {
    context.save();
    context.restore();
    context.translate(value, value);
    context.scale(value, value);
    context.rotate(value);
  };

  template <usagi::concepts::floating_point ValueType>
  inline constexpr ValueType radians_to_degrees(ValueType radians) {
    constexpr auto half_turn = static_cast<ValueType>(180);
    constexpr auto pi = static_cast<ValueType>(3.14159265358979323846);
    return radians * half_turn / pi;
  }

  template <class DrawContextType, class TransformType, class PointType, class FunctionType>
  void draw_with_transform(DrawContextType &context, const TransformType &transform,
                           const PointType &origin, FunctionType &&draw) {
    using value_type = typename std::remove_cvref_t<TransformType>::value_type;

    if constexpr (draw_transform_context<DrawContextType, value_type>) {
      const auto scale = transform.scale();
      const auto rotation = transform.rotation();
      const auto is_identity = scale.x() == static_cast<value_type>(1) &&
          scale.y() == static_cast<value_type>(1) && rotation == static_cast<value_type>(0);

      if (is_identity) {
        std::forward<FunctionType>(draw)();
        return;
      }

      context.save();
      context.translate(origin.x(), origin.y());
      context.rotate(radians_to_degrees(rotation));
      context.scale(scale.x(), scale.y());
      context.translate(-origin.x(), -origin.y());
      std::forward<FunctionType>(draw)();
      context.restore();
    } else {
      std::forward<FunctionType>(draw)();
    }
  }
} // namespace detail

/// Draws with scale and rotation applied to a transform-aware draw context.
///
/// Translation remains represented by the existing draw offset. When the draw
/// context exposes `save`, `restore`, `translate`, `scale`, and `rotate`, this
/// helper applies scale and rotation around `offset + transform.origin()` before
/// invoking `draw`. Contexts without those methods draw unchanged.
///
/// @param context Mutable drawing context.
/// @param transform Transform to apply.
/// @param offset Current accumulated draw offset.
/// @param draw Callable that performs the actual draw operation.
template <class DrawContextType, class FunctionType>
void draw_with_transform(DrawContextType &context,
                         const usagi::concepts::geometry::transform_concept auto &transform,
                         const usagi::concepts::geometry::point_concept auto &offset,
                         FunctionType &&draw) {
  const auto origin = offset + transform.origin();
  detail::draw_with_transform(context, transform, origin, std::forward<FunctionType>(draw));
}
} // namespace usagi::ui
