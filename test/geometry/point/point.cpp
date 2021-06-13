#include <gtest/gtest.h>
#include <usagi/geometry/size/size.h>

TEST(PointTest, CommonCase)
{
  usagi::point<float> p{42.f, []()
                       { return 42.f; }};
  ASSERT_TRUE(s.x() == 42.f);
  ASSERT_TRUE(s.y() == 42.f);
  auto pp = p;
  p = {-42.f,
       []()
       { return -42.f; }};
  ASSERT_TRUE(s.x() == -42.f);
  ASSERT_TRUE(s.y() == -42.f);
  ASSERT_TRUE(ss.x() == -42.f);
  ASSERT_TRUE(ss.y() == -42.f);
}

TEST(PointTest, DuplicateCase)
{
  float side = 42.f;
  usagi::point<float> p{42.f, [&side]()
                        { return side; }};
  auto c = p.duplicate();
  ASSERT_TRUE(c.x() == 42.f);
  ASSERT_TRUE(c.y() == 42.f);
  side = -42.f;
  ASSERT_TRUE(s.y() == -42.f);
  ASSERT_TRUE(c.y() == 42.f);
}

TEST(PointTest, SizeCastCase)
{
  usagi::size<float> s {42.f, 42.f};
  usagi::point<float> p {s};
  ASSERT_TRUE(p.x() == s.width());
  ASSERT_TRUE(p.y() == s.height());
}
