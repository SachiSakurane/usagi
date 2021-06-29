#include <gtest/gtest.h>
#include <usagi/concepts/geometry/point_concept.h>
#include <usagi/geometry/point/point.h>

bool PointStaticTest()
{
  static_assert(usagi::concepts::geometry::point_concept<usagi::geometry::point<int>>);

  return true;
}

TEST(PointTest, StaticCase)
{
  ASSERT_TRUE(PointStaticTest());
}

TEST(PointTest, CommonCase)
{
  usagi::geometry::point<float> p{42.f, []()
                                  { return 42.f; }};
  ASSERT_TRUE(p.x() == 42.f);
  ASSERT_TRUE(p.y() == 42.f);
  usagi::geometry::point<float> pp = p;
  p = {-42.f,
       []()
       { return -42.f; }};
  ASSERT_TRUE(p.x() == -42.f);
  ASSERT_TRUE(p.y() == -42.f);
  ASSERT_TRUE(pp.x() == 42.f);
  ASSERT_TRUE(pp.y() == 42.f);
}

TEST(PointTest, DuplicateCase)
{
  float side = 42.f;
  usagi::geometry::point<float> p{42.f, [&side]()
                                  { return side; }};
  auto c = p.duplicate();
  ASSERT_TRUE(c.x() == 42.f);
  ASSERT_TRUE(c.y() == 42.f);
  side = -42.f;
  ASSERT_TRUE(p.y() == -42.f);
  ASSERT_TRUE(c.y() == 42.f);
}

TEST(PointTest, SizeCastCase)
{
  usagi::geometry::size<float> s{42.f, 42.f};
  auto p = usagi::geometry::point<float>{s};
  ASSERT_TRUE(p.x() == s.width());
  ASSERT_TRUE(p.y() == s.height());
}
