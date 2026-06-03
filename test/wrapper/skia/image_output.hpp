#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <utility>

#include <gtest/gtest.h>

#include "include/core/SkColor.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkRect.h"
#include "include/core/SkSurface.h"

namespace usagi::test::skia {
inline constexpr std::string_view image_output_dir() {
#if defined(USAGI_SKIA_IMAGE_OUTPUT_DIR)
  return USAGI_SKIA_IMAGE_OUTPUT_DIR;
#else
  return {};
#endif
}

inline std::string current_test_name() {
  const auto *info = testing::UnitTest::GetInstance()->current_test_info();
  if (info == nullptr) {
    return "UnknownTest.UnknownCase";
  }

  return std::string{info->test_suite_name()} + "." + info->name();
}

inline std::string image_file_name(std::string_view kind) {
  return current_test_name() + "." + std::string{kind} + ".ppm";
}

inline void write_ppm(const SkPixmap &pixmap, const std::filesystem::path &path) {
  std::filesystem::create_directories(path.parent_path());

  std::ofstream file{path, std::ios::binary};
  ASSERT_TRUE(file.is_open()) << "failed to open " << path;

  file << "P6\n" << pixmap.width() << ' ' << pixmap.height() << "\n255\n";
  for (int y = 0; y < pixmap.height(); ++y) {
    for (int x = 0; x < pixmap.width(); ++x) {
      const SkColor color = pixmap.getColor(x, y);
      const unsigned char rgb[] = {
          static_cast<unsigned char>(SkColorGetR(color)),
          static_cast<unsigned char>(SkColorGetG(color)),
          static_cast<unsigned char>(SkColorGetB(color)),
      };
      file.write(reinterpret_cast<const char *>(rgb), sizeof(rgb));
    }
  }
}

inline void write_actual_image(const SkPixmap &pixmap, std::string_view name) {
#if defined(USAGI_SKIA_WRITE_IMAGES)
  write_ppm(pixmap, std::filesystem::path{std::string{image_output_dir()}} / name);
#else
  (void) pixmap;
  (void) name;
#endif
}

inline void write_actual_image(const SkPixmap &pixmap) {
  write_actual_image(pixmap, image_file_name("actual"));
}

inline void write_expected_image(const SkPixmap &pixmap, std::string_view name) {
#if defined(USAGI_SKIA_WRITE_IMAGES)
  write_ppm(pixmap, std::filesystem::path{std::string{image_output_dir()}} / name);
#else
  (void) pixmap;
  (void) name;
#endif
}

inline void write_expected_image(const SkPixmap &pixmap) {
  write_expected_image(pixmap, image_file_name("expected"));
}

inline void draw_diff_image(const SkPixmap &actual, const SkPixmap &expected, SkCanvas &canvas) {
  ASSERT_EQ(actual.width(), expected.width());
  ASSERT_EQ(actual.height(), expected.height());

  canvas.clear(SK_ColorWHITE);

  SkPaint paint;
  paint.setColor(SkColorSetRGB(255, 0, 255));
  for (int y = 0; y < actual.height(); ++y) {
    for (int x = 0; x < actual.width(); ++x) {
      if (actual.getColor(x, y) != expected.getColor(x, y)) {
        canvas.drawRect(SkRect::MakeXYWH(static_cast<float>(x), static_cast<float>(y), 1.f, 1.f),
                        paint);
      }
    }
  }
}

inline void write_diff_image(const SkPixmap &actual, const SkPixmap &expected,
                             std::string_view name) {
#if defined(USAGI_SKIA_WRITE_IMAGES)
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(actual.width(), actual.height()));
  ASSERT_NE(surface, nullptr);

  draw_diff_image(actual, expected, *surface->getCanvas());

  SkPixmap diff;
  ASSERT_TRUE(surface->peekPixels(&diff));
  write_ppm(diff, std::filesystem::path{std::string{image_output_dir()}} / name);
#else
  (void) actual;
  (void) expected;
  (void) name;
#endif
}

inline void write_diff_image(const SkPixmap &actual, const SkPixmap &expected) {
  write_diff_image(actual, expected, image_file_name("diff"));
}

template <class DrawFunction>
inline void write_expected_image(int width, int height, std::string_view name, DrawFunction &&draw) {
#if defined(USAGI_SKIA_WRITE_IMAGES)
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(width, height));
  ASSERT_NE(surface, nullptr);

  draw(*surface->getCanvas());

  SkPixmap pixmap;
  ASSERT_TRUE(surface->peekPixels(&pixmap));
  write_expected_image(pixmap, name);
#else
  (void) width;
  (void) height;
  (void) name;
  (void) draw;
#endif
}

template <class DrawFunction>
inline void write_expected_image(int width, int height, DrawFunction &&draw) {
  write_expected_image(width, height, image_file_name("expected"), std::forward<DrawFunction>(draw));
}

template <class DrawFunction>
inline void write_expected_and_diff_image(const SkPixmap &actual, int width, int height,
                                          std::string_view expected_name,
                                          std::string_view diff_name, DrawFunction &&draw) {
#if defined(USAGI_SKIA_WRITE_IMAGES)
  auto surface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(width, height));
  ASSERT_NE(surface, nullptr);

  draw(*surface->getCanvas());

  SkPixmap expected;
  ASSERT_TRUE(surface->peekPixels(&expected));
  write_expected_image(expected, expected_name);
  write_diff_image(actual, expected, diff_name);
#else
  (void) actual;
  (void) width;
  (void) height;
  (void) expected_name;
  (void) diff_name;
  (void) draw;
#endif
}

template <class DrawFunction>
inline void write_expected_and_diff_image(const SkPixmap &actual, int width, int height,
                                          DrawFunction &&draw) {
  write_expected_and_diff_image(actual, width, height, image_file_name("expected"),
                                image_file_name("diff"), std::forward<DrawFunction>(draw));
}

inline void expect_color(const SkPixmap &pixmap, int x, int y, SkColor expected) {
  EXPECT_EQ(pixmap.getColor(x, y), expected) << "at (" << x << ", " << y << ")";
}
} // namespace usagi::test::skia
