#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>

#include <gtest/gtest.h>

#include "include/core/SkColor.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkSurface.h"

namespace usagi::test::skia {
inline constexpr std::string_view image_output_dir() {
#if defined(USAGI_SKIA_IMAGE_OUTPUT_DIR)
  return USAGI_SKIA_IMAGE_OUTPUT_DIR;
#else
  return {};
#endif
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

inline void write_expected_image(const SkPixmap &pixmap, std::string_view name) {
#if defined(USAGI_SKIA_WRITE_IMAGES)
  write_ppm(pixmap, std::filesystem::path{std::string{image_output_dir()}} / name);
#else
  (void) pixmap;
  (void) name;
#endif
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

inline void expect_color(const SkPixmap &pixmap, int x, int y, SkColor expected) {
  EXPECT_EQ(pixmap.getColor(x, y), expected) << "at (" << x << ", " << y << ")";
}
} // namespace usagi::test::skia
