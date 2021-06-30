#include <gtest/gtest.h>
#include <usagi/concepts/geometry/point_concept.h>
#include <usagi/geometry/point/point.h>

namespace
{
  static_assert(usagi::concepts::geometry::point_concept<usagi::geometry::point<int>>);
}

TEST(PointTest, ConstructorCase)
{
  {
    usagi::geometry::point<float> p{};
    ASSERT_EQ(p.x(), 0);
    ASSERT_EQ(p.y(), 0);
  }

  {
    usagi::geometry::point<float> p{42.f, []()
                                    { return 42.f; }};
    ASSERT_EQ(p.x(), 42.f);
    ASSERT_EQ(p.y(), 42.f);
  }

  {
    float side = 42.f;
    usagi::geometry::point p{
        usagi::geometry::size<float>{
            42.f, [&side]()
            { return side; }}};
    ASSERT_EQ(p.x(), 42.f);
    ASSERT_EQ(p.y(), 42.f);
    side = 20;
    ASSERT_EQ(p.y(), 20.f);
  }
}

TEST(PointTest, CommonCase)
{
  usagi::geometry::point<float> p{42.f, []()
                                  { return 42.f; }};
  ASSERT_EQ(p.x(), 42.f);
  ASSERT_EQ(p.y(), 42.f);
  usagi::geometry::point<float> pp = p;
  p = {-42.f,
       []()
       { return -42.f; }};
  ASSERT_EQ(p.x(), -42.f);
  ASSERT_EQ(p.y(), -42.f);
  ASSERT_EQ(pp.x(), 42.f);
  ASSERT_EQ(pp.y(), 42.f);
}

TEST(PointTest, DuplicateCase)
{
  float side = 42.f;
  usagi::geometry::point<float> p{42.f, [&side]()
                                  { return side; }};
  auto c = p.duplicate();
  ASSERT_EQ(c.x(), 42.f);
  ASSERT_EQ(c.y(), 42.f);
  side = -42.f;
  ASSERT_EQ(p.y(), -42.f);
  ASSERT_EQ(c.y(), 42.f);
}

TEST(PointTest, SizeCastCase)
{
  usagi::geometry::size<float> s{42.f, 42.f};
  auto p = usagi::geometry::point<float>{s};
  ASSERT_EQ(p.x(), s.width());
  ASSERT_EQ(p.y(), s.height());
}
