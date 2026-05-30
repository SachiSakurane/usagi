#include <gtest/gtest.h>
#include <usagi/geometry/algorithm/duplicate.hpp>
#include <usagi/geometry/point.hpp>
#include <usagi/geometry/rect.hpp>
#include <usagi/geometry/size.hpp>

TEST(GeometryAlgorithmTest, DuplicateCase) {
  {
    float side = 42.f;
    usagi::geometry::variable_point<float> p{[&side]() { return std::make_tuple(42.f, side); }};
    auto c = usagi::geometry::duplicate(p);
    ASSERT_EQ(p, c);
    side = 10.f;
    ASSERT_NE(p, c);
  }
  {
    float height = 24.f;
    usagi::geometry::variable_size<float> s{
        [&height]() { return std::make_tuple(42.f, height); }};
    auto c = usagi::geometry::duplicate(s);
    ASSERT_EQ(s, c);
    height = 12.f;
    ASSERT_NE(s, c);
  }
  {
    float right = 42.f;
    usagi::geometry::variable_rect<float> r{
        [&right]() { return std::make_tuple(2.f, 4.f, right, 24.f); }};
    auto c = usagi::geometry::duplicate(r);
    ASSERT_EQ(r, c);
    right = 20.f;
    ASSERT_NE(r, c);
  }
}
