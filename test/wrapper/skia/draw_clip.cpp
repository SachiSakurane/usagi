#include <gtest/gtest.h>

#include <usagi/geometry/rect/rect.hpp>
#include <usagi/ui/draw_clip.hpp>
#include <usagi/wrapper/skia/draw_clip.hpp>

#include "drawing_helpers.hpp"
#include "image_output.hpp"

#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkRect.h"
#include "include/core/SkSurface.h"

namespace {
using usagi::test::skia::attempted_color;
using usagi::test::skia::background_color;
using usagi::test::skia::fill_rect;
using usagi::test::skia::guide_color;
using usagi::test::skia::result_color;

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

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 40, 40, [](SkCanvas &expected) {
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

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 50, 50, [](SkCanvas &expected) {
        expected.clear(SK_ColorWHITE);
        fill_rect(expected, 10.f, 10.f, 30.f, 30.f, SK_ColorRED);
        fill_rect(expected, 0.f, 0.f, 10.f, 10.f, SK_ColorBLUE);
      });

  usagi::test::skia::expect_color(pixmap, 5, 5, SK_ColorBLUE);
  usagi::test::skia::expect_color(pixmap, 25, 25, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 45, 45, SK_ColorWHITE);
}

TEST(SkiaDrawClipTest, IntersectsNestedClips) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(60, 60));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(background_color);
  fill_rect(*canvas, 10.f, 10.f, 40.f, 40.f, attempted_color);
  fill_rect(*canvas, 25.f, 5.f, 20.f, 30.f, guide_color);

  usagi::ui::draw_with_clip(*canvas, usagi::geometry::rect<float>{10.f, 10.f, 50.f, 50.f}, [&] {
    usagi::ui::draw_with_clip(*canvas, usagi::geometry::rect<float>{25.f, 5.f, 45.f, 35.f}, [&] {
      SkPaint paint;
      paint.setColor(result_color);
      canvas->drawRect(SkRect::MakeXYWH(0.f, 0.f, 60.f, 60.f), paint);
    });
  });

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 60, 60, [](SkCanvas &expected) {
        expected.clear(background_color);
        fill_rect(expected, 10.f, 10.f, 40.f, 40.f, attempted_color);
        fill_rect(expected, 25.f, 5.f, 20.f, 30.f, guide_color);
        fill_rect(expected, 25.f, 10.f, 20.f, 25.f, result_color);
      });

  usagi::test::skia::expect_color(pixmap, 15, 15, attempted_color);
  usagi::test::skia::expect_color(pixmap, 30, 7, guide_color);
  usagi::test::skia::expect_color(pixmap, 25, 10, result_color);
  usagi::test::skia::expect_color(pixmap, 44, 34, result_color);
  usagi::test::skia::expect_color(pixmap, 45, 35, attempted_color);
}
} // namespace
