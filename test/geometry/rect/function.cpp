#include <gtest/gtest.h>
#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/rect.hpp>

TEST(RectFunctionTest, MakeCase) {
  auto r = usagi::geometry::make_from_center(usagi::geometry::point<float>{10.f, 10.f},
                                             usagi::geometry::size<float>{20.f, 20.f});
  ASSERT_EQ(r, (usagi::geometry::rect<float>{0.f, 0.f, 20.f, 20.f}));
}

TEST(RectFunctionTest, TransformCase) {
  usagi::geometry::rect<float> r{0.f, 0.f, 40.f, 40.f};
  ASSERT_EQ(usagi::geometry::transform(r, 2.f, 2.f),
            (usagi::geometry::rect<float>{2.f, 2.f, 42.f, 42.f}));
}

TEST(RectFunctionTest, FromCase) {
  usagi::geometry::rect<float> r{2.f, 4.f, 42.f, 24.f};
  {
    auto rr = usagi::geometry::from_left(r, 10.f);
    ASSERT_EQ(rr.l(), 2.f);
    ASSERT_EQ(rr.r(), 12.f);
  }
  {
    auto rr = usagi::geometry::from_top(r, 10.f);
    ASSERT_EQ(rr.t(), 4.0f);
    ASSERT_EQ(rr.b(), 14.0f);
  }
  {
    auto rr = usagi::geometry::from_right(r, 10.0);
    ASSERT_EQ(rr.l(), 32.f);
    ASSERT_EQ(rr.r(), 42.f);
  }
  {
    auto rr = usagi::geometry::from_bottom(r, 10.f);
    ASSERT_EQ(rr.t(), 14.0f);
    ASSERT_EQ(rr.b(), 24.0f);
  }
  {
    auto rr = usagi::geometry::from_width(r, 42.f);
    ASSERT_EQ(rr.size().width(), 42.f);
  }
  {
    auto rr = usagi::geometry::from_height(r, 42.f);
    ASSERT_EQ(rr.size().height(), 42.f);
  }
}

TEST(RectFunctionTest, ReduceFromCase) {
  usagi::geometry::rect<float> rect{0.f, 0.f, 42.f, 42.f};
  {
    auto rr = usagi::geometry::reduce_from_left(rect, 1.f);
    ASSERT_EQ(rr.l(), 1.f);
    ASSERT_EQ(rr.size().width(), 41.f);
  }
  {
    auto rr = usagi::geometry::reduce_from_top(rect, 1.f);
    ASSERT_EQ(rr.t(), 1.f);
    ASSERT_EQ(rr.size().height(), 41.f);
  }
  {
    auto rr = usagi::geometry::reduce_from_right(rect, 2.f);
    ASSERT_EQ(rr.r(), 40.f);
    ASSERT_EQ(rr.size().width(), 40.f);
  }
  {
    auto rr = usagi::geometry::reduce_from_bottom(rect, 2.f);
    ASSERT_EQ(rr.b(), 40.f);
    ASSERT_EQ(rr.size().height(), 40.f);
  }
}

TEST(RectFunctionTest, ContainCase) {
  usagi::geometry::rect<float> a{0.f, 0.f, 42.f, 42.f};
  ASSERT_TRUE(usagi::geometry::contain(a, usagi::geometry::point<float>{3.f, 4.f}));
  ASSERT_FALSE(usagi::geometry::contain(a, usagi::geometry::point<float>{-3.f, 4.f}));
}

TEST(RectFunctionTest, PaddingCase) {
  {
    usagi::geometry::rect<float> a{0.f, 0.f, 42.f, 42.f};
    ASSERT_EQ(usagi::geometry::padding(a, 16.f),
              (usagi::geometry::rect<float>{16.f, 16.f, 26.f, 26.f}));
    ASSERT_EQ(usagi::geometry::padding(a, 30.f),
              (usagi::geometry::rect<float>{21.f, 21.f, 21.f, 21.f}));
  }
  {
    usagi::geometry::rect<float> a{0.f, 0.f, 42.f, 42.f};
    ASSERT_EQ(usagi::geometry::padding_width(a, 16.f),
              (usagi::geometry::rect<float>{16.f, 0.f, 26.f, 42.f}));
  }
  {
    usagi::geometry::rect<float> a{0.f, 0.f, 42.f, 42.f};
    ASSERT_EQ(usagi::geometry::padding_height(a, 16.f),
              (usagi::geometry::rect<float>{0.f, 16.f, 42.f, 26.f}));
  }
}
