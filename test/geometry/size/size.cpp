#include <gtest/gtest.h>
#include <usagi/concepts/geometry/size_concept.h>
#include <usagi/geometry/size/size.h>

bool SizeStaticTest()
{
  static_assert(usagi::concepts::geometry::size_concept<usagi::geometry::size<int>>);
  static_assert(usagi::concepts::geometry::size_concept<usagi::geometry::paired_size<int>>);

  return true;
}

TEST(SizeTest, StaticCase)
{
  ASSERT_TRUE(SizeStaticTest());
}

TEST(SizeTest, ConstructorCase)
{
  {
    usagi::geometry::size<float> s{};
    ASSERT_TRUE(s.width() == 0);
    ASSERT_TRUE(s.height() == 0);
  }

  {
    usagi::geometry::size<float> s{42.f, []()
                                   { return 42.f; }};
    ASSERT_TRUE(s.width() == 42.f);
    ASSERT_TRUE(s.height() == 42.f);
  }
}

TEST(SizeTest, CommonCase)
{
  usagi::geometry::size<float> s{42.f, []()
                                 { return 42.f; }};
  ASSERT_TRUE(s.width() == 42);
  ASSERT_TRUE(s.height() == 42);
  auto ss = s;
  s = {24.f,
       []()
       { return 24.f; }};
  ASSERT_TRUE(s.width() == 24);
  ASSERT_TRUE(s.height() == 24);
  ASSERT_TRUE(ss.width() == 42);
  ASSERT_TRUE(ss.height() == 42);
}

TEST(SizeTest, DuplicateCase)
{
  float side = 42.f;
  usagi::geometry::size<float> s{42.f, [&side]()
                                 { return side; }};
  auto c = s.duplicate();
  ASSERT_TRUE(c.width() == 42);
  ASSERT_TRUE(c.height() == 42);
  side = 20;
  ASSERT_TRUE(s.height() == 20);
  ASSERT_TRUE(c.height() == 42);
}
