#include <gtest/gtest.h>
#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_parameter<float>;
class SpecificView final : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {
public:
  SpecificView() = default;
  explicit SpecificView(const usagi::concepts::geometry::rect_concept auto &frame)
      : usagi::ui::base_view<float, DrawContext, GestureParameterType>{frame} {}
};
} // namespace

TEST(ViewCommonTest, MakeCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  ASSERT_TRUE(v.has_view());
  ASSERT_TRUE(static_cast<bool>(v));
}

TEST(ViewCommonTest, ConstructMoveCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  auto &vv = v.operator=(std::move(v));
  ASSERT_TRUE(static_cast<bool>(vv));
}

TEST(ViewCommonTest, MoveLeavesSourceEmptyCase) {
  auto source = usagi::ui::make_view<SpecificView>();
  auto moved = std::move(source);

  ASSERT_FALSE(source.has_view());
  ASSERT_FALSE(static_cast<bool>(source));
  ASSERT_TRUE(moved.has_view());
  ASSERT_TRUE(static_cast<bool>(moved));
}

TEST(ViewCommonTest, CommonCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  ASSERT_TRUE(v.is_enabled());
  v.set_enabled(false);
  ASSERT_FALSE(v.is_enabled());
}

TEST(ViewCommonTest, TransformCase) {
  auto v = usagi::ui::make_view<SpecificView>();

  v.set_transform(decltype(v)::transform_type{decltype(v)::point_type{1.f, 2.f}, 3.f,
                                              decltype(v)::point_type{4.f, 5.f},
                                              decltype(v)::point_type{6.f, 7.f}});
  ASSERT_EQ(v.transform().translation(), (decltype(v)::point_type{1.f, 2.f}));
  ASSERT_EQ(v.transform().rotation(), 3.f);
  ASSERT_EQ(v.transform().scale(), (decltype(v)::point_type{4.f, 5.f}));
  ASSERT_EQ(v.transform().origin(), (decltype(v)::point_type{6.f, 7.f}));

  v.set_translation(decltype(v)::point_type{8.f, 9.f});
  v.set_rotation(14.f, decltype(v)::point_type{15.f, 16.f});
  ASSERT_EQ(v.transform().origin(), (decltype(v)::point_type{15.f, 16.f}));
  v.set_scale(decltype(v)::point_type{10.f, 11.f}, decltype(v)::point_type{12.f, 13.f});

  ASSERT_EQ(v.translation(), (decltype(v)::point_type{8.f, 9.f}));
  ASSERT_EQ(v.rotation(), 14.f);
  ASSERT_EQ(v.scale(), (decltype(v)::point_type{10.f, 11.f}));
  ASSERT_EQ(v.transform().origin(), (decltype(v)::point_type{12.f, 13.f}));
}

TEST(ViewCommonTest, BoundsCase) {
  auto v = usagi::ui::make_view<SpecificView>(usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f});
  ASSERT_EQ(v.bounds(), (usagi::geometry::size<float>{30.f, 30.f}));
  ASSERT_EQ(v.frame(), (usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}));
}

TEST(ViewCommonTest, PredicationCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  ASSERT_TRUE(v.has_view());
  ASSERT_TRUE(static_cast<bool>(v));
}

TEST(ViewCommonTest, DrawCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  auto context = DrawContext{};
  v.draw(context, typename SpecificView::offset_type{});
}
