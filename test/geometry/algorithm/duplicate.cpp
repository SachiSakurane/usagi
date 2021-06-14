#include <gtest/gtest.h>
#include <usagi/geometry/algorithm/duplicate.h>
#include <usagi/geometry/point.h>

TEST(GeometryAlgorithmTest, DuplicateCase)
{
  float side = 42.f;
  usagi::point<float> s{42.f, [&side]()
                        { return side; }};
  auto c = usagi::duplicate(s);
  ASSERT_TRUE(s == c);
  side = 10.f;
  ASSERT_TRUE(s != c);
}
