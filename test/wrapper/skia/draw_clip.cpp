#include <gtest/gtest.h>

#include <usagi/geometry/rect/rect.hpp>
#include <usagi/ui/draw_clip.hpp>
#include <usagi/wrapper/skia/draw_clip.hpp>

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
  canvas->clear(SK_ColorTRANSPARENT);

  usagi::ui::draw_with_clip(*canvas, usagi::geometry::rect<float>{1.f, 1.f, 3.f, 3.f}, [&] {
    SkPaint paint;
    paint.setColor(SK_ColorRED);
    canvas->drawRect(SkRect::MakeXYWH(0.f, 0.f, 4.f, 4.f), paint);
  });

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));

  EXPECT_EQ(*pixmap.addr32(0, 0), SK_ColorTRANSPARENT);
  EXPECT_EQ(*pixmap.addr32(1, 1), SK_ColorRED);
  EXPECT_EQ(*pixmap.addr32(2, 2), SK_ColorRED);
  EXPECT_EQ(*pixmap.addr32(3, 3), SK_ColorTRANSPARENT);
}
} // namespace
