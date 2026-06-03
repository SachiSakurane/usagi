#include <gtest/gtest.h>

#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/rect/rect.hpp>
#include <usagi/type/gesture.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/view.hpp>
#include <usagi/ui/view_stack.hpp>
#include <usagi/wrapper/skia/draw_clip.hpp>
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
using GestureParameterType = usagi::type::gesture_parameter<float>;
constexpr SkColor background_color = SkColorSetRGB(235, 235, 235);
constexpr SkColor guide_color = SkColorSetRGB(80, 160, 220);
constexpr SkColor attempted_color = SkColorSetRGB(150, 230, 230);
constexpr SkColor result_color = SkColorSetRGB(220, 60, 60);

void fill_rect(SkCanvas &canvas, float x, float y, float width, float height, SkColor color) {
  SkPaint paint;
  paint.setColor(color);
  canvas.drawRect(SkRect::MakeXYWH(x, y, width, height), paint);
}

class PaintView final : public usagi::ui::base_view<float, SkCanvas, GestureParameterType> {
public:
  using base_view_type = usagi::ui::base_view<float, SkCanvas, GestureParameterType>;
  using offset_type = typename base_view_type::offset_type;

  PaintView(const rect_type &frame, SkColor c) : base_view_type{frame}, color{c} {}

  void draw(draw_context_type &canvas, offset_type offset) override {
    SkPaint paint;
    paint.setColor(color);
    canvas.drawRect(SkRect::MakeXYWH(offset.x(), offset.y(), this->bounds().width(),
                                     this->bounds().height()),
                    paint);
  }

private:
  SkColor color;
};

TEST(SkiaViewStackTest, DrawOffsetIncludesChildTranslation) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(70, 70));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(background_color);
  fill_rect(*canvas, 10.f, 10.f, 20.f, 20.f, guide_color);

  auto stack = usagi::ui::view_stack<float, SkCanvas, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 70.f, 70.f}};
  const auto key = stack.add_child_view(usagi::ui::make_view<PaintView>(
      usagi::geometry::rect<float>{10.f, 10.f, 30.f, 30.f}, result_color));
  stack.get_child_view(key).set_translation(usagi::geometry::point<float>{20.f, 10.f});

  stack.draw(*canvas, usagi::geometry::point<float>{});

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(
      pixmap, "SkiaViewStackTest.DrawOffsetIncludesChildTranslation.actual.ppm");
  usagi::test::skia::write_expected_image(
      70, 70, "SkiaViewStackTest.DrawOffsetIncludesChildTranslation.expected.ppm",
      [](SkCanvas &expected) {
        expected.clear(background_color);
        fill_rect(expected, 10.f, 10.f, 20.f, 20.f, guide_color);
        fill_rect(expected, 30.f, 20.f, 20.f, 20.f, result_color);
      });

  usagi::test::skia::expect_color(pixmap, 10, 10, guide_color);
  usagi::test::skia::expect_color(pixmap, 30, 20, result_color);
  usagi::test::skia::expect_color(pixmap, 49, 39, result_color);
  usagi::test::skia::expect_color(pixmap, 55, 45, background_color);
}

TEST(SkiaViewStackTest, DrawClippingClipsToStackBoundsWhenEnabled) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(70, 70));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(background_color);
  fill_rect(*canvas, 10.f, 10.f, 60.f, 60.f, attempted_color);

  auto stack = usagi::ui::view_stack<float, SkCanvas, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 40.f, 40.f}};
  stack.set_draw_clipping(true);
  stack.add_child_view(usagi::ui::make_view<PaintView>(
      usagi::geometry::rect<float>{0.f, 0.f, 60.f, 60.f}, result_color));

  stack.draw(*canvas, usagi::geometry::point<float>{10.f, 10.f});

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(
      pixmap, "SkiaViewStackTest.DrawClippingClipsToStackBoundsWhenEnabled.actual.ppm");
  usagi::test::skia::write_expected_image(
      70, 70, "SkiaViewStackTest.DrawClippingClipsToStackBoundsWhenEnabled.expected.ppm",
      [](SkCanvas &expected) {
        expected.clear(background_color);
        fill_rect(expected, 10.f, 10.f, 60.f, 60.f, attempted_color);
        fill_rect(expected, 10.f, 10.f, 40.f, 40.f, result_color);
      });

  usagi::test::skia::expect_color(pixmap, 5, 5, background_color);
  usagi::test::skia::expect_color(pixmap, 10, 10, result_color);
  usagi::test::skia::expect_color(pixmap, 49, 49, result_color);
  usagi::test::skia::expect_color(pixmap, 55, 55, attempted_color);
}

TEST(SkiaViewStackTest, DrawClippingAppliesOutsideChildTransform) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(80, 80));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(background_color);
  fill_rect(*canvas, 10.f, 10.f, 70.f, 70.f, attempted_color);

  auto stack = usagi::ui::view_stack<float, SkCanvas, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 40.f, 40.f}};
  stack.set_draw_clipping(true);
  const auto key = stack.add_child_view(usagi::ui::make_view<PaintView>(
      usagi::geometry::rect<float>{0.f, 0.f, 40.f, 40.f}, result_color));
  stack.get_child_view(key).set_scale(usagi::geometry::point<float>{2.f, 2.f},
                                      usagi::geometry::point<float>{0.f, 0.f});

  stack.draw(*canvas, usagi::geometry::point<float>{10.f, 10.f});

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(
      pixmap, "SkiaViewStackTest.DrawClippingAppliesOutsideChildTransform.actual.ppm");
  usagi::test::skia::write_expected_image(
      80, 80, "SkiaViewStackTest.DrawClippingAppliesOutsideChildTransform.expected.ppm",
      [](SkCanvas &expected) {
        expected.clear(background_color);
        fill_rect(expected, 10.f, 10.f, 70.f, 70.f, attempted_color);
        fill_rect(expected, 10.f, 10.f, 40.f, 40.f, result_color);
      });

  usagi::test::skia::expect_color(pixmap, 10, 10, result_color);
  usagi::test::skia::expect_color(pixmap, 49, 49, result_color);
  usagi::test::skia::expect_color(pixmap, 60, 60, attempted_color);
}
} // namespace
