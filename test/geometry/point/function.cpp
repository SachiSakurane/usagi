#include <gtest/gtest.h>
#include <usagi/geometry/point/function.h>
#include <usagi/geometry/point/operator.h>

TEST(PointFunctionTest, MathCase)
{
  usagi::point<float> a{0.f, 0.f};
  usagi::point<float> b{3.f, 4.f};
  ASSERT_TRUE(usagi::distance(a, b)() == 5.f);
}

TEST(PointFunctionTest, DuplicateCase)
{
  float side = 42.f;
  usagi::point<float> s{42.f, [&side]()
                        { return side; }};
  auto c = usagi::duplicate(s);
  ASSERT_TRUE(s == c);
  side = 10.f;
  ASSERT_TRUE(s != c);
}
