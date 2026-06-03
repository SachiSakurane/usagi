#include <gtest/gtest.h>

#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/transform/transform.hpp>
#include <usagi/ui/draw_transform.hpp>
#include <usagi/wrapper/skia/draw_transform.hpp>

#include "image_output.hpp"

#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkRect.h"
#include "include/core/SkSurface.h"

namespace {
constexpr auto pi = 3.14159265358979323846f;

TEST(SkiaDrawTransformTest, ScalesAroundOffsetOrigin) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(5, 5));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(SK_ColorWHITE);

  const auto transform = usagi::geometry::transform<float>{
      usagi::geometry::point<float>{}, 0.f, usagi::geometry::point<float>{2.f, 2.f},
      usagi::geometry::point<float>{}};

  usagi::ui::draw_with_transform(*canvas, transform, usagi::geometry::point<float>{}, [&] {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    canvas->drawRect(SkRect::MakeXYWH(1.f, 1.f, 1.f, 1.f), paint);
  });

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap,
                                        "SkiaDrawTransformTest.ScalesAroundOffsetOrigin.actual.ppm");

  usagi::test::skia::expect_color(pixmap, 1, 1, SK_ColorWHITE);
  usagi::test::skia::expect_color(pixmap, 2, 2, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 3, 3, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 4, 4, SK_ColorWHITE);
}

TEST(SkiaDrawTransformTest, RotatesAroundOffsetOrigin) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(5, 5));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(SK_ColorWHITE);

  const auto transform = usagi::geometry::transform<float>{
      usagi::geometry::point<float>{}, pi / 2.f, usagi::geometry::point<float>{1.f, 1.f},
      usagi::geometry::point<float>{1.f, 1.f}};

  usagi::ui::draw_with_transform(*canvas, transform, usagi::geometry::point<float>{1.f, 1.f}, [&] {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    canvas->drawRect(SkRect::MakeXYWH(3.f, 2.f, 1.f, 1.f), paint);
  });

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(
      pixmap, "SkiaDrawTransformTest.RotatesAroundOffsetOrigin.actual.ppm");

  usagi::test::skia::expect_color(pixmap, 1, 3, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 3, 2, SK_ColorWHITE);
}

TEST(SkiaDrawTransformTest, RotatesFortyFiveDegreesAroundOffsetOrigin) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(9, 9));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(SK_ColorWHITE);

  const auto transform = usagi::geometry::transform<float>{
      usagi::geometry::point<float>{}, pi / 4.f, usagi::geometry::point<float>{1.f, 1.f},
      usagi::geometry::point<float>{4.f, 4.f}};

  usagi::ui::draw_with_transform(*canvas, transform, usagi::geometry::point<float>{}, [&] {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    canvas->drawRect(SkRect::MakeXYWH(4.f, 1.f, 1.f, 6.f), paint);
  });

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(
      pixmap, "SkiaDrawTransformTest.RotatesFortyFiveDegreesAroundOffsetOrigin.actual.ppm");

  usagi::test::skia::expect_color(pixmap, 5, 2, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 4, 4, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 2, 5, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 4, 1, SK_ColorWHITE);
  usagi::test::skia::expect_color(pixmap, 4, 6, SK_ColorWHITE);
}
} // namespace
