#include <gtest/gtest.h>
#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/rect.hpp>

TEST(RectFunctionTest, ContainCase)
{
  usagi::geometry::rect<float> a{0.f, 0.f, 42.f, 42.f};
  ASSERT_TRUE(usagi::geometry::contain(a, usagi::geometry::point<float>{3.f, 4.f}));
  ASSERT_FALSE(usagi::geometry::contain(a, usagi::geometry::point<float>{-3.f, 4.f}));
}

TEST(RectFunctionTest, PaddingCase)
{
  usagi::geometry::rect<float> a{0.f, 0.f, 42.f, 42.f};
  ASSERT_EQ(usagi::geometry::padding(a, 16.f), (usagi::geometry::rect<float>{16.f, 16.f, 26.f, 26.f}));
  ASSERT_EQ(usagi::geometry::padding(a, 30.f), (usagi::geometry::rect<float>{21.f, 21.f, 21.f, 21.f}));
}
