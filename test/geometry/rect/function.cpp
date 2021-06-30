#include <gtest/gtest.h>
#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/rect/function.hpp>
#include <usagi/geometry/rect/rect.hpp>

TEST(RectFunctionTest, ContainCase)
{
  usagi::geometry::rect<float> a{0.f, 0.f, 42.f, 42.f};
  ASSERT_TRUE(usagi::geometry::contain(a, usagi::geometry::point<float>{3.f, 4.f}));
  ASSERT_FALSE(usagi::geometry::contain(a, usagi::geometry::point<float>{-3.f, 4.f}));
}
