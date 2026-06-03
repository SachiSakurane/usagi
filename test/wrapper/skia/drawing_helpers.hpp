#pragma once

#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkPaint.h"
#include "include/core/SkRect.h"

namespace usagi::test::skia {
constexpr SkColor background_color = SkColorSetRGB(235, 235, 235);
constexpr SkColor guide_color = SkColorSetRGB(80, 160, 220);
constexpr SkColor attempted_color = SkColorSetRGB(150, 230, 230);
constexpr SkColor result_color = SkColorSetRGB(220, 60, 60);
constexpr SkColor diff_color = SkColorSetRGB(255, 0, 255);

inline void fill_rect(SkCanvas &canvas, float x, float y, float width, float height,
                      SkColor color) {
  SkPaint paint;
  paint.setColor(color);
  canvas.drawRect(SkRect::MakeXYWH(x, y, width, height), paint);
}

inline void fill_pixel(SkCanvas &canvas, int x, int y, SkColor color) {
  fill_rect(canvas, static_cast<float>(x), static_cast<float>(y), 1.f, 1.f, color);
}
} // namespace usagi::test::skia
