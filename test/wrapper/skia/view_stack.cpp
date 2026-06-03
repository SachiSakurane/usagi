#include <gtest/gtest.h>

#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/rect/rect.hpp>
#include <usagi/type/gesture.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/view.hpp>
#include <usagi/ui/view_stack.hpp>
#include <usagi/wrapper/skia/draw_clip.hpp>
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
using GestureParameterType = usagi::type::gesture_parameter<float>;
using usagi::test::skia::attempted_color;
using usagi::test::skia::background_color;
using usagi::test::skia::fill_rect;
using usagi::test::skia::guide_color;
using usagi::test::skia::result_color;

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

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 70, 70, [](SkCanvas &expected) {
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

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 70, 70, [](SkCanvas &expected) {
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

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 80, 80, [](SkCanvas &expected) {
        expected.clear(background_color);
        fill_rect(expected, 10.f, 10.f, 70.f, 70.f, attempted_color);
        fill_rect(expected, 10.f, 10.f, 40.f, 40.f, result_color);
      });

  usagi::test::skia::expect_color(pixmap, 10, 10, result_color);
  usagi::test::skia::expect_color(pixmap, 49, 49, result_color);
  usagi::test::skia::expect_color(pixmap, 60, 60, attempted_color);
}

TEST(SkiaViewStackTest, DrawsChildrenInZOrder) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(110, 60));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(background_color);

  auto stack = usagi::ui::view_stack<float, SkCanvas, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 50.f, 50.f}};
  const auto back = stack.add_child_view(usagi::ui::make_view<PaintView>(
      usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}, guide_color));
  stack.add_child_view(usagi::ui::make_view<PaintView>(
      usagi::geometry::rect<float>{20.f, 20.f, 45.f, 45.f}, result_color));

  stack.draw(*canvas, usagi::geometry::point<float>{});
  ASSERT_TRUE(stack.bring_child_to_front(back));
  stack.draw(*canvas, usagi::geometry::point<float>{60.f, 0.f});

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 110, 60, [](SkCanvas &expected) {
        expected.clear(background_color);
        fill_rect(expected, 10.f, 10.f, 30.f, 30.f, guide_color);
        fill_rect(expected, 20.f, 20.f, 25.f, 25.f, result_color);
        fill_rect(expected, 80.f, 20.f, 25.f, 25.f, result_color);
        fill_rect(expected, 70.f, 10.f, 30.f, 30.f, guide_color);
      });

  usagi::test::skia::expect_color(pixmap, 15, 15, guide_color);
  usagi::test::skia::expect_color(pixmap, 25, 25, result_color);
  usagi::test::skia::expect_color(pixmap, 85, 25, guide_color);
  usagi::test::skia::expect_color(pixmap, 104, 44, result_color);
}

TEST(SkiaViewStackTest, SkipsDisabledChildrenWhenDrawing) {
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(60, 60));

  ASSERT_NE(surface, nullptr);

  SkCanvas *canvas = surface->getCanvas();
  canvas->clear(background_color);

  auto stack = usagi::ui::view_stack<float, SkCanvas, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 60.f, 60.f}};
  stack.add_child_view(usagi::ui::make_view<PaintView>(
      usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}, guide_color));
  const auto disabled = stack.add_child_view(usagi::ui::make_view<PaintView>(
      usagi::geometry::rect<float>{20.f, 20.f, 50.f, 50.f}, result_color));
  stack.get_child_view(disabled).set_enabled(false);

  stack.draw(*canvas, usagi::geometry::point<float>{});

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  usagi::test::skia::write_actual_image(pixmap);
  usagi::test::skia::write_expected_and_diff_image(
      pixmap, 60, 60, [](SkCanvas &expected) {
        expected.clear(background_color);
        fill_rect(expected, 10.f, 10.f, 30.f, 30.f, guide_color);
      });

  usagi::test::skia::expect_color(pixmap, 15, 15, guide_color);
  usagi::test::skia::expect_color(pixmap, 25, 25, guide_color);
  usagi::test::skia::expect_color(pixmap, 45, 45, background_color);
}
} // namespace
