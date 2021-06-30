#include <gtest/gtest.h>
#include <usagi/concepts/graphics/color_concept.hpp>
#include <usagi/graphics/color/color.hpp>

namespace
{
  static_assert(usagi::concepts::graphics::color_concept<usagi::graphics::color<int>>);
  static_assert(usagi::concepts::graphics::color_concept<usagi::graphics::paired_color<int>>);
}

TEST(ColorTest, CommonCase)
{
  usagi::graphics::color<float> c{
      42.f,
      4.2f,
      0.42f,
      []()
      { return 0.042f; }};
  ASSERT_EQ(c.r(), 42.f);
  ASSERT_EQ(c.g(), 4.2f);
  ASSERT_EQ(c.b(), 0.42f);
  ASSERT_EQ(c.a(), 0.042f);
  auto cc = c;
  c = {24.f,
       2.4f,
       0.24f,
       []()
       { return 0.024f; }};
  ASSERT_EQ(c.r(), 24.f);
  ASSERT_EQ(c.a(), 0.024f);
  ASSERT_EQ(cc.r(), 42.f);
  ASSERT_EQ(cc.a(), 0.042f);
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
  ASSERT_EQ(copied.r(), 42.f);
  ASSERT_EQ(copied.a(), 0.042f);
  side = 20.f;
  ASSERT_EQ(c.a(), 20.f);
  ASSERT_EQ(copied.a(), 0.042f);
}
