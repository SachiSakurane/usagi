#include <gtest/gtest.h>
#include <usagi/geometry/rect/operator.h>

TEST(RectOperatorTest, CmpCase)
{
  usagi::rect<float> r{0.f, 0.f, 42.f, 42.f};
  ASSERT_TRUE((r == usagi::rect<float>{0.f, 0.f, 42.f, 42.f}));
  ASSERT_TRUE((r != usagi::rect<float>{0.f, 0.f, 42.f, 40.f}));
}

TEST(RectOperatorTest, AuthmeticCase)
{
  usagi::rect<float> r{0.f, 0.f, 40.f, 40.f};
  usagi::point<float> p{2.f, 2.f};
  ASSERT_TRUE((r + p == usagi::rect<float>{2.f, 2.f, 42.f, 42.f}));
  ASSERT_TRUE((r - p == usagi::rect<float>{-2.f, -2.f, 38.f, 38.f}));
}
