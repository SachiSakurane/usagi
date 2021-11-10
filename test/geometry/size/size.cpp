#include <gtest/gtest.h>
#include <usagi/geometry/size/size.hpp>

TEST(SizeTest, ConstructorCase) {
  {
    usagi::geometry::size<float> s{};
    ASSERT_EQ(s.width(), 0);
    ASSERT_EQ(s.height(), 0);
  }

  {
    usagi::geometry::size<float> s{42.f, 24.f};
    ASSERT_EQ(s.width(), 42.f);
    ASSERT_EQ(s.height(), 24.f);
  }

  {
    usagi::geometry::variable_size<float> s{[]() { return std::make_tuple(42.f, 24.f); }};
    ASSERT_EQ(s.width(), 42.f);
    ASSERT_EQ(s.height(), 24.f);
  }

  {
    float side = 42.f;
    usagi::geometry::variable_size<float> p{[&side]() { return std::make_tuple(42.f, side); }};
    ASSERT_EQ(p.width(), 42.f);
    ASSERT_EQ(p.height(), 42.f);
    side = 20;
    ASSERT_EQ(p.height(), 20.f);
  }
}

TEST(SizeTest, BindCase) {
  {
    usagi::geometry::size<float> s{42.f, 24.f};
    auto [w, h] = s();
    ASSERT_EQ(s.width(), w);
    ASSERT_EQ(s.height(), h);
  }

  {
    usagi::geometry::variable_size<float> s{[]() { return std::make_tuple(42.f, 24.f); }};
    auto [w, h] = s();
    ASSERT_EQ(s.width(), w);
    ASSERT_EQ(s.height(), h);
  }
}
