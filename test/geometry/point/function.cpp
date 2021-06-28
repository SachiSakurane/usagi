#include <gtest/gtest.h>
#include <usagi/geometry/point/function.h>
#include <usagi/geometry/point/point.h>

TEST(PointFunctionTest, MathCase)
{
  usagi::point<float> a{0.f, 0.f};
  usagi::point<float> b{3.f, 4.f};
  ASSERT_TRUE(usagi::distance(a, b)() == 5.f);
}
