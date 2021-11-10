#include <gtest/gtest.h>
#include <usagi/graphics/color/color.hpp>

TEST(ColorTest, CommonCase) {
  usagi::graphics::basic_color<float> c{0.042f, 42.f, 4.2f, 0.42f};
  ASSERT_EQ(c.red(), 42.f);
  ASSERT_EQ(c.green(), 4.2f);
  ASSERT_EQ(c.blue(), 0.42f);
  ASSERT_EQ(c.alpha(), 0.042f);
  auto cc = c;
  c = {0.024f, 24.f, 2.4f, 0.24f};
  ASSERT_EQ(c.red(), 24.f);
  ASSERT_EQ(c.alpha(), 0.024f);
  ASSERT_EQ(cc.red(), 42.f);
  ASSERT_EQ(cc.alpha(), 0.042f);
}

TEST(ColorTest, DuplicateCase) {
  float side = 0.042f;
  usagi::graphics::variable_color<float> c{[&side]() { return side; }, 42.f, 4.2f, 0.42f};
  auto copied = c.duplicate();
  ASSERT_EQ(copied.red(), 42.f);
  ASSERT_EQ(copied.alpha(), 0.042f);
  side = 20.f;
  ASSERT_EQ(c.alpha(), 20.f);
  ASSERT_EQ(copied.alpha(), 0.042f);
}
