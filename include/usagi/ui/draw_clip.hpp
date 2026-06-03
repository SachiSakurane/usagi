#pragma once

#include <type_traits>
#include <utility>

#include <usagi/concepts/geometry/rect_concept.hpp>

namespace usagi::ui {
/// Context-specific draw clipping behavior.
///
/// Specialize this traits type for draw contexts that can clip drawing. The
/// default implementation leaves the context unclipped and only invokes `draw`.
///
/// @tparam DrawContextType Draw context type to adapt.
template <class DrawContextType>
struct draw_clip_traits {
  /// Draws without applying clipping operations.
  ///
  /// @param context Mutable drawing context.
  /// @param rect Clipping rectangle that an adapter may apply.
  /// @param draw Callable that performs the actual draw operation.
  static void draw(DrawContextType &context,
                   const usagi::concepts::geometry::rect_concept auto &rect, auto &&draw) {
    std::forward<decltype(draw)>(draw)();
  }
};

/// Draws with a context-specific clipping adapter.
///
/// Specialize `draw_clip_traits` for a draw context to clip drawing before
/// invoking `draw`. Contexts without a specialization draw unchanged.
///
/// @param context Mutable drawing context.
/// @param rect Clipping rectangle to apply.
/// @param draw Callable that performs the actual draw operation.
template <class DrawContextType, class FunctionType>
void draw_with_clip(DrawContextType &context,
                    const usagi::concepts::geometry::rect_concept auto &rect,
                    FunctionType &&draw) {
  usagi::ui::draw_clip_traits<std::remove_cvref_t<DrawContextType>>::draw(
      context, rect, std::forward<FunctionType>(draw));
}
} // namespace usagi::ui
