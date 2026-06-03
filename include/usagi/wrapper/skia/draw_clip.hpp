#pragma once

#include <utility>

#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/ui/draw_clip.hpp>
#include <usagi/wrapper/skia/to_skrect.hpp>

#include "include/core/SkCanvas.h"

namespace usagi::ui {
/// Skia draw clipping adapter.
///
/// Applies an intersecting rectangle clip using Skia's `save`, `clipRect`, and
/// `restore` calls, then invokes `draw`.
template <>
struct draw_clip_traits<SkCanvas> {
  /// Draws with a clipping rectangle applied to a Skia canvas.
  ///
  /// @param canvas Skia canvas to clip for the duration of `draw`.
  /// @param rect Clipping rectangle to apply.
  /// @param draw Callable that performs the actual draw operation.
  static void draw(SkCanvas &canvas,
                   const usagi::concepts::geometry::rect_concept auto &rect, auto &&draw) {
    canvas.save();
    canvas.clipRect(usagi::wrapper::skia::to_skrect(rect));
    std::forward<decltype(draw)>(draw)();
    canvas.restore();
  }
};
} // namespace usagi::ui
