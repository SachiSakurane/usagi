#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_default_parameter<float>;
class SpecificView final : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {};

// static test
static_assert(
    usagi::concepts::ui::viewable<usagi::ui::view<float, DrawContext, GestureParameterType>>,
    "usagi::ui::view<float, DrawContextable> has viewable concept");
static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{SpecificView{}})>,
              "view is constructable from SpecificView");
static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{(SpecificView{})})>,
              "view is constructable from SpecificView");
} // namespace

TEST(ViewCommonTest, ConstructMoveCase) {
  auto v = usagi::ui::view{SpecificView{}};
  auto &vv = v.operator=(std::move(v));
  ASSERT_TRUE(static_cast<bool>(vv));
}

TEST(ViewCommonTest, CommonCase) {
  auto v = usagi::ui::view{SpecificView{}};
  ASSERT_TRUE(v.is_enabled());
  v.set_enabled(false);
  ASSERT_FALSE(v.is_enabled());
}

TEST(ViewCommonTest, BoundsCase) {
  auto v = usagi::ui::view{usagi::ui::base_view<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}}};
  ASSERT_EQ(v.bounds(), (usagi::geometry::size<float>{30.f, 30.f}));
  ASSERT_EQ(v.frame(), (usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}));
}

TEST(ViewCommonTest, PredicationCase) {
  {
    // default constructor case
    auto v = usagi::ui::view<float, DrawContext, GestureParameterType>{};
    ASSERT_FALSE(static_cast<bool>(v));
  }
  {
    auto v = usagi::ui::view{SpecificView{}};
    ASSERT_TRUE(static_cast<bool>(v));
  }
}

TEST(ViewCommonTest, DrawCase) {
  auto v = usagi::ui::view{SpecificView{}};
  auto context = DrawContext{};
  v.draw(context);

  // sub case
  v.add_sub_view(usagi::ui::base_view<float, DrawContext, GestureParameterType>{});
  v.draw(context);
}

TEST(ViewCommonTest, MakeCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  ASSERT_TRUE(static_cast<bool>(v));
}
