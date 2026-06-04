#include <gtest/gtest.h>
#include <usagi/geometry/transform/function.hpp>
#include <usagi/geometry/transform/transform.hpp>
#include <usagi/math/constants.hpp>

namespace {
void expect_near_point(const usagi::geometry::point<float> &actual,
                       const usagi::geometry::point<float> &expected) {
  EXPECT_NEAR(actual.x(), expected.x(), 0.0001f);
  EXPECT_NEAR(actual.y(), expected.y(), 0.0001f);
}
} // namespace

TEST(TransformFunctionTest, RotatesPointAroundOrigin) {
  const auto transform =
      usagi::geometry::transform<float>{usagi::geometry::point<float>{10.f, 20.f},
                                        usagi::math::half_pi<float>,
                                        usagi::geometry::point<float>{2.f, 3.f},
                                        usagi::geometry::point<float>{5.f, 7.f}};

  const auto local = usagi::geometry::point<float>{8.f, 9.f};
  const auto transformed = usagi::geometry::transform_point(transform, local);

  expect_near_point(transformed, usagi::geometry::point<float>{9.f, 33.f});
  expect_near_point(usagi::geometry::inverse_transform_point(transform, transformed), local);
}
