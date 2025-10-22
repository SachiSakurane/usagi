#include <gtest/gtest.h>
#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/rect/operator.hpp>
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
  ASSERT_TRUE(static_cast<bool>(v));
}

TEST(ViewCommonTest, ConstructMoveCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  auto &vv = v.operator=(std::move(v));
  ASSERT_TRUE(static_cast<bool>(vv));
}

TEST(ViewCommonTest, CommonCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  ASSERT_TRUE(v.is_enabled());
  v.set_enabled(false);
  ASSERT_FALSE(v.is_enabled());
}

TEST(ViewCommonTest, BoundsCase) {
  auto v = usagi::ui::make_view<SpecificView>(usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f});
  ASSERT_EQ(v.bounds(), (usagi::geometry::size<float>{30.f, 30.f}));
  ASSERT_EQ(v.frame(), (usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}));
}

TEST(ViewCommonTest, PredicationCase) {
  {
    // default construct case
    auto v = usagi::ui::view<float, DrawContext, GestureParameterType>{};
    ASSERT_FALSE(static_cast<bool>(v));
  }
  {
    auto v = usagi::ui::make_view<SpecificView>();
    ASSERT_TRUE(static_cast<bool>(v));
  }
}

TEST(ViewCommonTest, DrawCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  auto context = DrawContext{};
  v.draw(context, typename SpecificView::offset_type{});
}
