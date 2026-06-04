#include <gtest/gtest.h>

#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/transform/transform.hpp>
#include <usagi/math/constants.hpp>
#include <usagi/ui/draw_transform.hpp>
#include <usagi/wrapper/skia/draw_transform.hpp>

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
using usagi::test::skia::background_color;
using usagi::test::skia::fill_rect;
using usagi::test::skia::guide_color;
using usagi::test::skia::result_color;

TEST(SkiaDrawTransformTest, ScalesAroundOffsetOrigin) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(50, 50));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(SK_ColorWHITE);

  const auto transform = usagi::geometry::transform<float>{
      usagi::geometry::point<float>{}, 0.f, usagi::geometry::point<float>{2.f, 2.f},
      usagi::geometry::point<float>{}};

  usagi::ui::draw_with_transform(*canvas, transform, usagi::geometry::point<float>{}, [&] {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    canvas->drawRect(SkRect::MakeXYWH(10.f, 10.f, 10.f, 10.f), paint);
  });

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 50, 50, [](SkCanvas &expected) {
        expected.clear(SK_ColorWHITE);
        fill_rect(expected, 20.f, 20.f, 20.f, 20.f, SK_ColorRED);
      });

  usagi::test::skia::expect_color(pixmap, 10, 10, SK_ColorWHITE);
  usagi::test::skia::expect_color(pixmap, 20, 20, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 39, 39, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 45, 45, SK_ColorWHITE);
}

TEST(SkiaDrawTransformTest, RotatesAroundOffsetOrigin) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(60, 60));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(SK_ColorWHITE);

  SkPaint guide_paint;
  guide_paint.setColor(SK_ColorBLUE);
  canvas->drawRect(SkRect::MakeXYWH(30.f, 15.f, 20.f, 10.f), guide_paint);

  const auto transform = usagi::geometry::transform<float>{
      usagi::geometry::point<float>{}, usagi::math::half_pi<float>,
      usagi::geometry::point<float>{1.f, 1.f},
      usagi::geometry::point<float>{10.f, 10.f}};

  usagi::ui::draw_with_transform(*canvas, transform, usagi::geometry::point<float>{10.f, 10.f}, [&] {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    canvas->drawRect(SkRect::MakeXYWH(30.f, 15.f, 20.f, 10.f), paint);
  });

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 60, 60, [](SkCanvas &expected) {
        expected.clear(SK_ColorWHITE);
        fill_rect(expected, 30.f, 15.f, 20.f, 10.f, SK_ColorBLUE);
        fill_rect(expected, 15.f, 30.f, 10.f, 20.f, SK_ColorRED);
      });

  usagi::test::skia::expect_color(pixmap, 20, 40, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 24, 49, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 40, 20, SK_ColorBLUE);
  usagi::test::skia::expect_color(pixmap, 30, 30, SK_ColorWHITE);
}

TEST(SkiaDrawTransformTest, RotatesFortyFiveDegreesAroundOffsetOrigin) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(90, 90));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(SK_ColorWHITE);

  const auto transform = usagi::geometry::transform<float>{
      usagi::geometry::point<float>{}, usagi::math::quarter_pi<float>,
      usagi::geometry::point<float>{1.f, 1.f},
      usagi::geometry::point<float>{40.f, 40.f}};

  usagi::ui::draw_with_transform(*canvas, transform, usagi::geometry::point<float>{}, [&] {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    canvas->drawRect(SkRect::MakeXYWH(40.f, 10.f, 10.f, 60.f), paint);
  });

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 90, 90, [](SkCanvas &expected) {
        expected.clear(SK_ColorWHITE);
        SkPaint paint;
        paint.setColor(SK_ColorRED);
        expected.save();
        expected.translate(40.f, 40.f);
        expected.rotate(45.f);
        expected.translate(-40.f, -40.f);
        expected.drawRect(SkRect::MakeXYWH(40.f, 10.f, 10.f, 60.f), paint);
        expected.restore();
      });

  usagi::test::skia::expect_color(pixmap, 55, 25, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 40, 40, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 25, 55, SK_ColorRED);
  usagi::test::skia::expect_color(pixmap, 40, 10, SK_ColorWHITE);
  usagi::test::skia::expect_color(pixmap, 40, 70, SK_ColorWHITE);
}

TEST(SkiaDrawTransformTest, AppliesOffsetScaleAndRotationAroundOrigin) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(60, 60));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(background_color);
  fill_rect(*canvas, 25.f, 20.f, 10.f, 10.f, guide_color);

  const auto transform = usagi::geometry::transform<float>{
      usagi::geometry::point<float>{}, usagi::math::quarter_pi<float>,
      usagi::geometry::point<float>{2.f, 1.f},
      usagi::geometry::point<float>{10.f, 10.f}};
  const auto offset = usagi::geometry::point<float>{20.f, 5.f};

  usagi::ui::draw_with_transform(*canvas, transform, offset, [&] {
    SkPaint paint;
    paint.setColor(result_color);
    canvas->drawRect(SkRect::MakeXYWH(25.f, 20.f, 10.f, 10.f), paint);
  });

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 60, 60, [](SkCanvas &expected) {
        expected.clear(background_color);
        fill_rect(expected, 25.f, 20.f, 10.f, 10.f, guide_color);

        SkPaint paint;
        paint.setColor(result_color);
        expected.save();
        expected.translate(30.f, 15.f);
        expected.rotate(45.f);
        expected.scale(2.f, 1.f);
        expected.translate(-30.f, -15.f);
        expected.drawRect(SkRect::MakeXYWH(25.f, 20.f, 10.f, 10.f), paint);
        expected.restore();
      });

  usagi::test::skia::expect_color(pixmap, 20, 18, result_color);
  usagi::test::skia::expect_color(pixmap, 26, 30, result_color);
  usagi::test::skia::expect_color(pixmap, 33, 20, guide_color);
  usagi::test::skia::expect_color(pixmap, 35, 35, background_color);
}
} // namespace
