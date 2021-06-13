#include <gtest/gtest.h>
#include <usagi/geometry/size/operator.h>

TEST(SizeOperatorTest, CmpCase)
{
  usagi::size<float> s{42.f, 42.f};
  ASSERT_TRUE((s == usagi::size<float>{42.f, 42.f}));
  ASSERT_TRUE((s != usagi::size<float>{40.f, 42.f}));
}

TEST(SizeOperatorTest, AuthmeticCase)
{
  usagi::size<float> s1{40.f, 40.f};
  usagi::size<float> s2{2.f, 2.f};
  ASSERT_TRUE((s1 + 2.f == usagi::size<float>{42.f, 42.f}));
  ASSERT_TRUE((2.f + s1 == usagi::size<float>{42.f, 42.f}));
  ASSERT_TRUE((s1 + s2 == usagi::size<float>{42.f, 42.f}));
  ASSERT_TRUE((s1 - 2.f == usagi::size<float>{38.f, 38.f}));
  ASSERT_TRUE((s1 - s2 == usagi::size<float>{38.f, 38.f}));
  ASSERT_TRUE((42.f - s1 == usagi::size<float>{2.f, 2.f}));
  ASSERT_TRUE((s1 * 2.f == usagi::size<float>{80.f, 80.f}));
  ASSERT_TRUE((2.f * s1 == usagi::size<float>{80.f, 80.f}));
  ASSERT_TRUE((s1 * s2 == usagi::size<float>{80.f, 80.f}));
  ASSERT_TRUE((s1 / 2.f == usagi::size<float>{20.f, 20.f}));
  ASSERT_TRUE((s1 / s2 == usagi::size<float>{20.f, 20.f}));
  ASSERT_TRUE((2.f / s1 == usagi::size<float>{0.05f, 0.05f}));
}

TEST(SizeOperatorTest, AuthmeticSideEffectCase)
{
  float side1 = 40.f;
  usagi::size<float> s1{40.f, [&side1]()
                        { return side1; }};
  float side2 = 2.f;
  usagi::size<float> s2{2.f, [&side2]()
                        { return side2; }};
  ASSERT_TRUE((s1 + s2 == usagi::size<float>{42.f, 42.f}));
  side1 = 10.f;
  ASSERT_TRUE((s1 + s2 == usagi::size<float>{42.f, 12.f}));
  side2 = 5.f;
  ASSERT_TRUE((s1 + s2 == usagi::size<float>{42.f, 15.f}));

  auto s3 = s1 + s2.duplicate();
  ASSERT_TRUE((s1 + s2 == s3));
  side1 = 40.f;
  ASSERT_TRUE((s1 + s2 == s3));
  side2 = 2.f;
  ASSERT_TRUE((s1 + s2 != s3));
}
