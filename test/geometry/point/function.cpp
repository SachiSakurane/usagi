#include <gtest/gtest.h>
#include <usagi/geometry/point/function.hpp>
#include <usagi/geometry/point/point.hpp>

TEST(PointFunctionTest, MathCase) {
  usagi::geometry::point<float> a{0.f, 0.f};
  usagi::geometry::point<float> b{3.f, 4.f};
  ASSERT_EQ(usagi::geometry::distance(a, b), 5.f);
}
