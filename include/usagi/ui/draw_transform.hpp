#pragma once

#include <type_traits>
#include <utility>

#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/concepts/geometry/transform_concept.hpp>

namespace usagi::ui {
/// Context-specific draw transform behavior.
///
/// Specialize this traits type for draw contexts that can apply transforms.
/// The default implementation leaves the context unchanged and only invokes
/// `draw`.
///
/// @tparam DrawContextType Draw context type to adapt.
template <class DrawContextType>
struct draw_transform_traits {
  /// Draws without applying transform operations.
  ///
  /// @param context Mutable drawing context.
  /// @param transform Transform that an adapter may apply.
  /// @param offset Current accumulated draw offset.
  /// @param draw Callable that performs the actual draw operation.
  static void draw(DrawContextType &context,
                   const usagi::concepts::geometry::transform_concept auto &transform,
                   const usagi::concepts::geometry::point_concept auto &offset, auto &&draw) {
    std::forward<decltype(draw)>(draw)();
  }
};

/// Draws with a context-specific transform adapter.
///
/// Translation remains represented by the existing draw offset. Specialize
/// `draw_transform_traits` for a draw context to apply scale and rotation before
/// invoking `draw`. Contexts without a specialization draw unchanged.
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
  usagi::ui::draw_transform_traits<std::remove_cvref_t<DrawContextType>>::draw(
      context, transform, offset, std::forward<FunctionType>(draw));
}
} // namespace usagi::ui
