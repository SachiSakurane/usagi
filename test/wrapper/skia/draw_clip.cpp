#include <gtest/gtest.h>

#include <usagi/geometry/rect/rect.hpp>
#include <usagi/ui/draw_clip.hpp>
#include <usagi/wrapper/skia/draw_clip.hpp>

#include "image_output.hpp"

#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkRect.h"
#include "include/core/SkSurface.h"

namespace {
void fill_rect(SkCanvas &canvas, float x, float y, float width, float height, SkColor color) {
  SkPaint paint;
  paint.setColor(color);
  canvas.drawRect(SkRect::MakeXYWH(x, y, width, height), paint);
}

TEST(SkiaDrawClipTest, ClipsPixelsOutsideRect) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(40, 40));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(SK_ColorWHITE);

  usagi::ui::draw_with_clip(*canvas, usagi::geometry::rect<float>{10.f, 10.f, 30.f, 30.f}, [&] {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    canvas->drawRect(SkRect::MakeXYWH(0.f, 0.f, 40.f, 40.f), paint);
  });

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap,
                                        "SkiaDrawClipTest.ClipsPixelsOutsideRect.actual.ppm");
  usagi::test::skia::write_expected_image(
      40, 40, "SkiaDrawClipTest.ClipsPixelsOutsideRect.expected.ppm", [](SkCanvas &expected) {
        expected.clear(SK_ColorWHITE);
        fill_rect(expected, 10.f, 10.f, 20.f, 20.f, SK_ColorRED);
      });

  usagi::test::skia::expect_color(pixmap, 5, 5, SK_ColorWHITE);
  usagi::test::skia::expect_color(pixmap, 10, 10, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 29, 29, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 35, 35, SK_ColorWHITE);
}

TEST(SkiaDrawClipTest, RestoresClipAfterDraw) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(50, 50));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(SK_ColorWHITE);

  usagi::ui::draw_with_clip(*canvas, usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}, [&] {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    canvas->drawRect(SkRect::MakeXYWH(0.f, 0.f, 50.f, 50.f), paint);
  });

  SkPaint paint;
  paint.setColor(SK_ColorBLUE);
  canvas->drawRect(SkRect::MakeXYWH(0.f, 0.f, 10.f, 10.f), paint);

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap,
                                        "SkiaDrawClipTest.RestoresClipAfterDraw.actual.ppm");
  usagi::test::skia::write_expected_image(
      50, 50, "SkiaDrawClipTest.RestoresClipAfterDraw.expected.ppm", [](SkCanvas &expected) {
        expected.clear(SK_ColorWHITE);
        fill_rect(expected, 10.f, 10.f, 30.f, 30.f, SK_ColorRED);
        fill_rect(expected, 0.f, 0.f, 10.f, 10.f, SK_ColorBLUE);
      });

  usagi::test::skia::expect_color(pixmap, 5, 5, SK_ColorBLUE);
  usagi::test::skia::expect_color(pixmap, 25, 25, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 45, 45, SK_ColorWHITE);
}
} // namespace
