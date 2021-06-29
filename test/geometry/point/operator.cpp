#include <gtest/gtest.h>
#include <usagi/geometry/point/operator.h>

TEST(PointOperatorTest, CmpCase)
{
  usagi::geometry::point<float> p{42.f, -42.f};
  ASSERT_TRUE((p == usagi::geometry::point<float>{42.f, -42.f}));
  ASSERT_TRUE((p != usagi::geometry::point<float>{40.f, -42.f}));
}

TEST(PointOperatorTest, AuthmeticCase)
{
  usagi::geometry::point<float> s1{40.f, 40.f};
  usagi::geometry::point<float> s2{2.f, 2.f};
  ASSERT_TRUE((s1 + 2.f == usagi::geometry::point<float>{42.f, 42.f}));
  ASSERT_TRUE((2.f + s1 == usagi::geometry::point<float>{42.f, 42.f}));
  ASSERT_TRUE((s1 + s2 == usagi::geometry::point<float>{42.f, 42.f}));
  ASSERT_TRUE((s1 - 2.f == usagi::geometry::point<float>{38.f, 38.f}));
  ASSERT_TRUE((s1 - s2 == usagi::geometry::point<float>{38.f, 38.f}));
  ASSERT_TRUE((42.f - s1 == usagi::geometry::point<float>{2.f, 2.f}));
  ASSERT_TRUE((s1 * 2.f == usagi::geometry::point<float>{80.f, 80.f}));
  ASSERT_TRUE((2.f * s1 == usagi::geometry::point<float>{80.f, 80.f}));
  ASSERT_TRUE((s1 * s2 == usagi::geometry::point<float>{80.f, 80.f}));
  ASSERT_TRUE((s1 / 2.f == usagi::geometry::point<float>{20.f, 20.f}));
  ASSERT_TRUE((s1 / s2 == usagi::geometry::point<float>{20.f, 20.f}));
  ASSERT_TRUE((2.f / s1 == usagi::geometry::point<float>{0.05f, 0.05f}));
}
