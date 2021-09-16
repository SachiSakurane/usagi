#include <gtest/gtest.h>
#include <usagi/geometry/size/operator.hpp>

TEST(SizeOperatorTest, CmpCase) {
  usagi::geometry::size<float> s{42.f, 42.f};
  ASSERT_EQ(s, (usagi::geometry::size<float>{42.f, 42.f}));
  ASSERT_NE(s, (usagi::geometry::size<float>{40.f, 42.f}));
}

TEST(SizeOperatorTest, AuthmeticCase) {
  usagi::geometry::size<float> s1{40.f, 40.f};
  usagi::geometry::size<float> s2{2.f, 2.f};
  ASSERT_EQ(s1 + s2, (usagi::geometry::size<float>{42.f, 42.f}));
  ASSERT_EQ(s1 - s2, (usagi::geometry::size<float>{38.f, 38.f}));
  ASSERT_EQ(s1 * 2.f, (usagi::geometry::size<float>{80.f, 80.f}));
  ASSERT_EQ(2.f * s1, (usagi::geometry::size<float>{80.f, 80.f}));
  ASSERT_EQ(s1 / 2.f, (usagi::geometry::size<float>{20.f, 20.f}));
  ASSERT_EQ(2.f / s1, (usagi::geometry::size<float>{0.05f, 0.05f}));
}
