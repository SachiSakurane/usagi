#include <gtest/gtest.h>
#include <usagi/geometry/algorithm/duplicate.hpp>
#include <usagi/geometry/point.hpp>

TEST(GeometryAlgorithmTest, DuplicateCase) {
  {
    float side = 42.f;
    usagi::geometry::variable_point<float> p{[&side]() { return std::make_tuple(42.f, side); }};
    auto c = usagi::geometry::duplicate(p);
    ASSERT_EQ(p, c);
    side = 10.f;
    ASSERT_NE(p, c);
  }
}
