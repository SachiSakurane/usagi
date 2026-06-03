#include <gtest/gtest.h>

#include "image_output.hpp"

#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkRect.h"
#include "include/core/SkSurface.h"

namespace {
constexpr SkColor diff_color = SkColorSetRGB(255, 0, 255);

void fill_pixel(SkCanvas &canvas, int x, int y, SkColor color) {
  SkPaint paint;
  paint.setColor(color);
  canvas.drawRect(SkRect::MakeXYWH(static_cast<float>(x), static_cast<float>(y), 1.f, 1.f), paint);
}

TEST(SkiaImageOutputTest, DrawDiffImageMarksOnlyMismatchedPixels) {
  auto actual_surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(3, 2));
  auto expected_surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(3, 2));
  auto diff_surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(3, 2));

  ASSERT_NE(actual_surface, nullptr);
  ASSERT_NE(expected_surface, nullptr);
  ASSERT_NE(diff_surface, nullptr);

  actual_surface->getCanvas()->clear(SK_ColorWHITE);
  expected_surface->getCanvas()->clear(SK_ColorWHITE);

  fill_pixel(*actual_surface->getCanvas(), 1, 0, SK_ColorRED);
  fill_pixel(*expected_surface->getCanvas(), 1, 0, SK_ColorBLUE);

  SkPixmap actual;
  SkPixmap expected;
  SkPixmap diff;
  ASSERT_TRUE(actual_surface->peekPixels(&actual));
  ASSERT_TRUE(expected_surface->peekPixels(&expected));

  usagi::test::skia::draw_diff_image(actual, expected, *diff_surface->getCanvas());

  ASSERT_TRUE(diff_surface->peekPixels(&diff));
  usagi::test::skia::write_diff_image(
      actual, expected, "SkiaImageOutputTest.DrawDiffImageMarksOnlyMismatchedPixels.diff.ppm");

  usagi::test::skia::expect_color(diff, 0, 0, SK_ColorWHITE);
  usagi::test::skia::expect_color(diff, 1, 0, diff_color);
  usagi::test::skia::expect_color(diff, 2, 0, SK_ColorWHITE);
  usagi::test::skia::expect_color(diff, 0, 1, SK_ColorWHITE);
  usagi::test::skia::expect_color(diff, 1, 1, SK_ColorWHITE);
  usagi::test::skia::expect_color(diff, 2, 1, SK_ColorWHITE);
}
} // namespace
