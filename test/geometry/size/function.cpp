#include <gtest/gtest.h>
#include <usagi/geometry/size/function.h>
#include <usagi/geometry/size/operator.h>

TEST(SizeFunctionTest, DuplicateCase)
{
  float side = 42.f;
  usagi::size<float> s{42.f, [&side]()
                       { return side; }};
  auto c = usagi::duplicate(s);
  ASSERT_TRUE(s == c);
  side = 10.f;
  ASSERT_TRUE(s != c);
}
