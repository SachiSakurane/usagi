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
TEST(SkiaDrawClipTest, ClipsPixelsOutsideRect) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(4, 4));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(SK_ColorWHITE);

  usagi::ui::draw_with_clip(*canvas, usagi::geometry::rect<float>{1.f, 1.f, 3.f, 3.f}, [&] {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    canvas->drawRect(SkRect::MakeXYWH(0.f, 0.f, 4.f, 4.f), paint);
  });

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap,
                                        "SkiaDrawClipTest.ClipsPixelsOutsideRect.actual.ppm");

  usagi::test::skia::expect_color(pixmap, 0, 0, SK_ColorWHITE);
  usagi::test::skia::expect_color(pixmap, 1, 1, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 2, 2, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 3, 3, SK_ColorWHITE);
}

TEST(SkiaDrawClipTest, RestoresClipAfterDraw) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(5, 5));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(SK_ColorWHITE);

  usagi::ui::draw_with_clip(*canvas, usagi::geometry::rect<float>{1.f, 1.f, 4.f, 4.f}, [&] {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    canvas->drawRect(SkRect::MakeXYWH(0.f, 0.f, 5.f, 5.f), paint);
  });

  SkPaint paint;
  paint.setColor(SK_ColorBLUE);
  canvas->drawRect(SkRect::MakeXYWH(0.f, 0.f, 1.f, 1.f), paint);

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap,
                                        "SkiaDrawClipTest.RestoresClipAfterDraw.actual.ppm");

  usagi::test::skia::expect_color(pixmap, 0, 0, SK_ColorBLUE);
  usagi::test::skia::expect_color(pixmap, 2, 2, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 4, 4, SK_ColorWHITE);
}
} // namespace
