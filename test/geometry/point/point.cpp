#include <gtest/gtest.h>
#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/size/size.hpp>

namespace {
static_assert(usagi::concepts::geometry::point_concept<usagi::geometry::point<int>>);
static_assert(usagi::concepts::geometry::point_concept<usagi::geometry::variable_point<int>>);
}

TEST(PointTest, ConstructorCase) {
  {
    usagi::geometry::point<float> p{};
    ASSERT_EQ(p.x(), 0.f);
    ASSERT_EQ(p.y(), 0.f);
  }

  {
    usagi::geometry::point<float> p{42.f, 24.f};
    ASSERT_EQ(p.x(), 42.f);
    ASSERT_EQ(p.y(), 24.f);
  }

  {
    usagi::geometry::variable_point<float> p{[]() { return std::make_tuple(42.f, 24.f); }};
    ASSERT_EQ(p.x(), 42.f);
    ASSERT_EQ(p.y(), 24.f);
  }

  {
    float side = 42.f;
    usagi::geometry::variable_point<float> p{[&side]() { return std::make_tuple(42.f, side); }};
    ASSERT_EQ(p.x(), 42.f);
    ASSERT_EQ(p.y(), 42.f);
    side = 20;
    ASSERT_EQ(p.y(), 20.f);
  }
}

TEST(PointTest, BindCase) {
  {
    usagi::geometry::point<float> p{42.f, 24.f};
    auto [x, y] = p();
    ASSERT_EQ(p.x(), x);
    ASSERT_EQ(p.y(), y);
  }

  {
    usagi::geometry::variable_point<float> p{[]() { return std::make_tuple(42.f, 24.f); }};
    auto [x, y] = p();
    ASSERT_EQ(p.x(), x);
    ASSERT_EQ(p.y(), y);
  }
}

TEST(PointTest, SizeCastCase) {
  usagi::geometry::size<float> s{42.f, 42.f};
  auto p = usagi::geometry::point<float>{s};
  ASSERT_EQ(p.x(), s.width());
  ASSERT_EQ(p.y(), s.height());
}
