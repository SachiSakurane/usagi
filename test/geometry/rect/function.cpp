#include <gtest/gtest.h>
#include <usagi/geometry/point/point.h>
#include <usagi/geometry/rect/function.h>
#include <usagi/geometry/rect/rect.h>

TEST(RectFunctionTest, ContainCase)
{
  usagi::rect<float> a{0.f, 0.f, 42.f, 42.f};
  ASSERT_TRUE(usagi::contain(a, usagi::point<float>{3.f, 4.f}));
  ASSERT_FALSE(usagi::contain(a, usagi::point<float>{-3.f, 4.f}));
}
