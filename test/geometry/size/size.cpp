#include <gtest/gtest.h>
#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/geometry/size/size.hpp>

namespace
{
  static_assert(usagi::concepts::geometry::size_concept<usagi::geometry::size<int>>);
  static_assert(usagi::concepts::geometry::size_concept<usagi::geometry::tupled_size<int>>);
}

TEST(SizeTest, ConstructorCase)
{
  {
    usagi::geometry::size<float> s{};
    ASSERT_EQ(s.width(), 0);
    ASSERT_EQ(s.height(), 0);
  }

  {
    usagi::geometry::size<float> s{42.f, []()
                                   { return 42.f; }};
    ASSERT_EQ(s.width(), 42.f);
    ASSERT_EQ(s.height(), 42.f);
  }
}

TEST(SizeTest, CommonCase)
{
  usagi::geometry::size<float> s{42.f, []()
                                 { return 42.f; }};
  ASSERT_EQ(s.width(), 42);
  ASSERT_EQ(s.height(), 42);
  auto ss = s;
  s = {24.f,
       []()
       { return 24.f; }};
  ASSERT_EQ(s.width(), 24);
  ASSERT_EQ(s.height(), 24);
  ASSERT_EQ(ss.width(), 42);
  ASSERT_EQ(ss.height(), 42);
}

TEST(SizeTest, DuplicateCase)
{
  float side = 42.f;
  usagi::geometry::size<float> s{42.f, [&side]()
                                 { return side; }};
  auto c = s.duplicate();
  ASSERT_EQ(c.width(), 42);
  ASSERT_EQ(c.height(), 42);
  side = 20;
  ASSERT_EQ(s.height(), 20);
  ASSERT_EQ(c.height(), 42);
}
