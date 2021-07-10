#include <gtest/gtest.h>
#include <usagi/geometry/rect/operator.hpp>

TEST(RectOperatorTest, CmpCase) {
  usagi::geometry::rect<float> r{0.f, 0.f, 42.f, 42.f};
  ASSERT_EQ(r, (usagi::geometry::rect<float>{0.f, 0.f, 42.f, 42.f}));
  ASSERT_NE(r, (usagi::geometry::rect<float>{0.f, 0.f, 42.f, 40.f}));
}

TEST(RectOperatorTest, AuthmeticCase) {
  usagi::geometry::rect<float> r{0.f, 0.f, 40.f, 40.f};
  usagi::geometry::point<float> p{2.f, 2.f};
  ASSERT_EQ(r + p, (usagi::geometry::rect<float>{2.f, 2.f, 42.f, 42.f}));
  ASSERT_EQ(r - p, (usagi::geometry::rect<float>{-2.f, -2.f, 38.f, 38.f}));
}
