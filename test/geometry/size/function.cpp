#include <gtest/gtest.h>
#include <usagi/geometry/size/function.hpp>

TEST(SizeFunctionTest, AspectRatio) {
  {
    usagi::geometry::size<float> s{2.f, 1.f};
    ASSERT_EQ(usagi::geometry::aspect_ratio(s), 2.f);
  }
  {
    usagi::geometry::size<float> s{1.f, 2.f};
    ASSERT_EQ(usagi::geometry::aspect_ratio(s), 0.5f);
  }
}

#ifndef NDEBUG
TEST(SizeFunctionTest, ZeroHeightAspectRatioCase) {
  usagi::geometry::size<float> s{2.f, 0.f};
  ASSERT_DEATH((void)usagi::geometry::aspect_ratio(s), "");
}
#endif
