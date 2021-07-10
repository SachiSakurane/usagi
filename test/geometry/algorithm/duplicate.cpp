#include <gtest/gtest.h>
#include <usagi/geometry/algorithm/duplicate.hpp>
#include <usagi/geometry/point.hpp>

TEST(GeometryAlgorithmTest, DuplicateCase) {
  float side = 42.f;
  usagi::geometry::point<float> s{42.f, [&side]() { return side; }};
  auto c = usagi::geometry::duplicate(s);
  ASSERT_EQ(s, c);
  side = 10.f;
  ASSERT_NE(s, c);
}
