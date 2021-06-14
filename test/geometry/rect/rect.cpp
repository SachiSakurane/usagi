#include <gtest/gtest.h>
#include <usagi/geometry/rect/rect.h>

TEST(RectTest, CommonCase)
{
  float side = 42.f;
  usagi::rect<float> r{2.f, 2.f,
                       []()
                       { return 42.f; },
                       [&side]()
                       { return side; }};
  ASSERT_TRUE(r.l() == 2.f);
  ASSERT_TRUE(r.t() == 2.f);
  ASSERT_TRUE(r.r() == 42.f);
  ASSERT_TRUE(r.b() == 42.f);

  auto rr = r;
  side = 20.f;
  ASSERT_TRUE(rr.l() == 2.f);
  ASSERT_TRUE(rr.t() == 2.f);
  ASSERT_TRUE(rr.r() == 42.f);
  ASSERT_TRUE(rr.b() == 20.f);
}

TEST(RectTest, DuplicateCase)
{
  float side = 42.f;
  usagi::rect<float> r{2.f, 2.f,
                       []()
                       { return 42.f; },
                       [&side]()
                       { return side; }};
  auto c = r.duplicate();
  ASSERT_TRUE(c.l() == 2.f);
  ASSERT_TRUE(c.t() == 2.f);
  ASSERT_TRUE(c.r() == 42.f);
  ASSERT_TRUE(c.b() == 42.f);
  side = 20;
  ASSERT_TRUE(r.b() == 20);
  ASSERT_TRUE(c.b() == 42);
}
