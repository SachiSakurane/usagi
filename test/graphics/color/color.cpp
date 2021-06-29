#include <gtest/gtest.h>
#include <usagi/concepts/graphics/color_concept.h>
#include <usagi/graphics/color/color.h>

bool ColorStaticTest()
{
  static_assert(usagi::concepts::graphics::color_concept<usagi::graphics::color<int>>);
  static_assert(usagi::concepts::graphics::color_concept<usagi::graphics::paired_color<int>>);

  return true;
}

TEST(ColorTest, StaticCase)
{
  ASSERT_TRUE(ColorStaticTest());
}

TEST(ColorTest, CommonCase)
{
  usagi::graphics::color<float> c{
      42.f,
      4.2f,
      0.42f,
      []()
      { return 0.042f; }};
  ASSERT_TRUE(c.r() == 42.f);
  ASSERT_TRUE(c.g() == 4.2f);
  ASSERT_TRUE(c.b() == 0.42f);
  ASSERT_TRUE(c.a() == 0.042f);
  auto cc = c;
  c = {24.f,
       2.4f,
       0.24f,
       []()
       { return 0.024f; }};
  ASSERT_TRUE(c.r() == 24.f);
  ASSERT_TRUE(c.a() == 0.024f);
  ASSERT_TRUE(cc.r() == 42.f);
  ASSERT_TRUE(cc.a() == 0.042f);
}

TEST(ColorTest, DuplicateCase)
{
  float side = 0.042f;
  usagi::graphics::color<float> c{
      42.f,
      4.2f,
      0.42f, [&side]()
      { return side; }};
  auto copied = c.duplicate();
  ASSERT_TRUE(copied.r() == 42.f);
  ASSERT_TRUE(copied.a() == 0.042f);
  side = 20.f;
  ASSERT_TRUE(c.a() == 20.f);
  ASSERT_TRUE(copied.a() == 0.042f);
}
