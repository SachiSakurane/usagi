#include <gtest/gtest.h>
#include <usagi/geometry/rect/rect.hpp>

namespace {
static_assert(usagi::concepts::geometry::rect_concept<usagi::geometry::rect<int>>);
static_assert(usagi::concepts::geometry::rect_concept<usagi::geometry::variable_rect<int>>);
}

TEST(RectTest, ConstructorCase) {
  {
    usagi::geometry::rect<float> r{};
    ASSERT_EQ(r.l(), 0);
    ASSERT_EQ(r.t(), 0);
    ASSERT_EQ(r.r(), 0);
    ASSERT_EQ(r.b(), 0);
  }

  {
    usagi::geometry::rect<float> r{2.f, 4.f, 42.f, 24.f};
    ASSERT_EQ(r.l(), 2.f);
    ASSERT_EQ(r.t(), 4.f);
    ASSERT_EQ(r.r(), 42.f);
    ASSERT_EQ(r.b(), 24.f);
  }

  {
    usagi::geometry::rect r{usagi::geometry::size<float>{42.f, 24.f}};
    ASSERT_EQ(r.l(), 0);
    ASSERT_EQ(r.t(), 0);
    ASSERT_EQ(r.r(), 42.f);
    ASSERT_EQ(r.b(), 24.f);
    ASSERT_EQ(r.size(), (usagi::geometry::size<float>{42.f, 24.f}));
  }

  {
    usagi::geometry::rect r{
        usagi::geometry::variable_size<float>{[]() { return std::make_tuple(42.f, 24.f); }}};
    ASSERT_EQ(r.l(), 0);
    ASSERT_EQ(r.t(), 0);
    ASSERT_EQ(r.r(), 42.f);
    ASSERT_EQ(r.b(), 24.f);
  }

  {
    usagi::geometry::rect r{usagi::geometry::point<float>{2.f, 2.f},
                            usagi::geometry::size<float>{40.f, 40.f}};
    ASSERT_EQ(r.l(), 2.f);
    ASSERT_EQ(r.t(), 2.f);
    ASSERT_EQ(r.r(), 42.f);
    ASSERT_EQ(r.b(), 42.f);
    ASSERT_EQ(r.size(), (usagi::geometry::size<float>{40.f, 40.f}));
    ASSERT_EQ(r.center(), (usagi::geometry::point<float>{22.f, 22.f}));
  }

  {
    auto r{usagi::geometry::variable_rect<float>{
        []() { return std::make_tuple(2.f, 4.f, 42.f, 24.f); }}};
    ASSERT_EQ(r.l(), 2.f);
    ASSERT_EQ(r.t(), 4.f);
    ASSERT_EQ(r.r(), 42.f);
    ASSERT_EQ(r.b(), 24.f);
  }

  {
    float side = 42.f;
    auto r{usagi::geometry::variable_rect<float>{
        [&side]() { return std::make_tuple(2.f, 4.f, side, 24.f); }}};
    ASSERT_EQ(r.l(), 2.f);
    ASSERT_EQ(r.t(), 4.f);
    ASSERT_EQ(r.r(), 42.f);
    ASSERT_EQ(r.b(), 24.f);
    side = 20;
    ASSERT_EQ(r.r(), 20.f);
  }
}

TEST(RectTest, BindCase) {
  usagi::geometry::rect<float> rect{2.f, 4.f, 42.f, 24.f};
  auto [l, t, r, b] = rect();
  ASSERT_EQ(rect.l(), l);
  ASSERT_EQ(rect.t(), t);
  ASSERT_EQ(rect.r(), r);
  ASSERT_EQ(rect.b(), b);
}
