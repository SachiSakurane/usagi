#include <gtest/gtest.h>
#include <usagi/geometry/rect/rect.hpp>

TEST(RectTest, ConstructorCase) {
  {
    usagi::geometry::rect<float> r{};
    ASSERT_EQ(r.l(), 0);
    ASSERT_EQ(r.t(), 0);
    ASSERT_EQ(r.r(), 0);
    ASSERT_EQ(r.b(), 0);
  }

  {
    usagi::geometry::rect<float> r{2.f, 2.f, []() { return 42.f; }, []() { return 42.f; }};
    ASSERT_EQ(r.l(), 2.f);
    ASSERT_EQ(r.t(), 2.f);
    ASSERT_EQ(r.r(), 42.f);
    ASSERT_EQ(r.b(), 42.f);
  }

  {
    usagi::geometry::rect r{usagi::geometry::size<float>{42.f, []() { return 42.f; }}};
    ASSERT_EQ(r.l(), 0);
    ASSERT_EQ(r.t(), 0);
    ASSERT_EQ(r.r(), 42.f);
    ASSERT_EQ(r.b(), 42.f);
    ASSERT_EQ(r.size(), (usagi::geometry::size<float>{42.f, []() { return 42.f; }}));
  }

  {
    usagi::geometry::rect r{usagi::geometry::tupled_size<float>{std::make_tuple(42.f, 42.f)}};
    ASSERT_EQ(r.l(), 0);
    ASSERT_EQ(r.t(), 0);
    ASSERT_EQ(r.r(), 42.f);
    ASSERT_EQ(r.b(), 42.f);
  }

  {
    usagi::geometry::rect r{usagi::geometry::point<float>{2.f, []() { return 2.f; }},
                            usagi::geometry::size<float>{40.f, []() { return 40.f; }}};
    ASSERT_EQ(r.l(), 2.f);
    ASSERT_EQ(r.t(), 2.f);
    ASSERT_EQ(r.r(), 42.f);
    ASSERT_EQ(r.b(), 42.f);
    ASSERT_EQ(r.size(), (usagi::geometry::size<float>{40.f, []() { return 40.f; }}));
    ASSERT_EQ(r.center(), (usagi::geometry::point<float>{22.f, 22.f}));
  }

  {
    usagi::geometry::rect<float> r{
        usagi::geometry::tupled_rect<float>{std::make_tuple(2.f, 2.f, 42.f, 42.f)}};
    ASSERT_EQ(r.l(), 2.f);
    ASSERT_EQ(r.t(), 2.f);
    ASSERT_EQ(r.r(), 42.f);
    ASSERT_EQ(r.b(), 42.f);
  }
}

TEST(RectTest, CommonCase) {
  float side = 42.f;
  usagi::geometry::rect<float> r{2.f, 2.f, []() { return 42.f; }, [&side]() { return side; }};
  ASSERT_EQ(r.l(), 2.f);
  ASSERT_EQ(r.t(), 2.f);
  ASSERT_EQ(r.r(), 42.f);
  ASSERT_EQ(r.b(), 42.f);

  auto rr = r;
  side = 20.f;
  ASSERT_EQ(rr.l(), 2.f);
  ASSERT_EQ(rr.t(), 2.f);
  ASSERT_EQ(rr.r(), 42.f);
  ASSERT_EQ(rr.b(), 20.f);
}

TEST(RectTest, DuplicateCase) {
  float side = 42.f;
  usagi::geometry::rect<float> r{2.f, 2.f, []() { return 42.f; }, [&side]() { return side; }};
  auto c = r.duplicate();
  ASSERT_EQ(c.l(), 2.f);
  ASSERT_EQ(c.t(), 2.f);
  ASSERT_EQ(c.r(), 42.f);
  ASSERT_EQ(c.b(), 42.f);
  side = 20;
  ASSERT_EQ(r.b(), 20);
  ASSERT_EQ(c.b(), 42);
}
