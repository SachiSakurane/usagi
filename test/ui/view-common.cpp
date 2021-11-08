#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext {};
using MouseParameter = usagi::type::mouse::default_parameter<float>;
class SpecificView final : public usagi::ui::base_view<float, DrawContext, MouseParameter> {};

// static test
static_assert(usagi::concepts::ui::viewable<usagi::ui::view<float, DrawContext, MouseParameter>>,
              "usagi::ui::view<float, DrawContextable> has viewable concept");
static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{SpecificView{}})>,
              "view is constructable from SpecificView");
static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{(SpecificView{})})>,
              "view is constructable from SpecificView");
} // namespace

TEST(ViewCommonTest, CommonCase) {
  auto v = usagi::ui::view{SpecificView{}};
  auto &vv = v.operator=(std::move(v));
  ASSERT_TRUE(static_cast<bool>(vv));
}

TEST(ViewCommonTest, BoundsCase) {
  auto v = usagi::ui::view{usagi::ui::base_view<float, DrawContext, MouseParameter>{
      usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}}};
  ASSERT_EQ(v.bounds(), (usagi::geometry::size<float>{30.f, 30.f}));
  ASSERT_EQ(v.frame(), (usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}));
}

TEST(ViewCommonTest, PredicationCase) {
  {
    // default constructor case
    auto v = usagi::ui::view<float, DrawContext, MouseParameter>{};
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
  v.add_sub_view(usagi::ui::base_view<float, DrawContext, MouseParameter>{});
  v.draw(context);
}

TEST(ViewCommonTest, CommonSubViewCase) {
  auto v = usagi::ui::view{SpecificView{}};

  ASSERT_FALSE(v.remove_sub_view(0));

  {
    decltype(auto) sub = v.add_sub_view(SpecificView{});
    ASSERT_TRUE(static_cast<bool>(sub.second));
    decltype(auto) get_sub = v.get_sub_view(sub.first);
    ASSERT_EQ(&sub.second, &get_sub);
    ASSERT_TRUE(v.remove_sub_view(sub.first));
  }
  ASSERT_EQ(v.sub_view_size(), 0);

  decltype(auto) sub1 = v.add_sub_view(usagi::ui::base_view<float, DrawContext, MouseParameter>{});
  ASSERT_EQ(v.sub_view_size(), 1);

  decltype(auto) sub2 = v.add_sub_view(usagi::ui::base_view<float, DrawContext, MouseParameter>{});
  ASSERT_EQ(v.sub_view_size(), 2);

  ASSERT_TRUE(v.remove_sub_view(sub1.first));
  ASSERT_EQ(v.sub_view_size(), 1);

  ASSERT_TRUE(v.remove_sub_view(sub2.first));
  ASSERT_EQ(v.sub_view_size(), 0);

  ASSERT_FALSE(v.remove_sub_view(0));
}

TEST(ViewCommonTest, ClickCase) {
  auto v = usagi::ui::view{SpecificView{}};
  v.event(SpecificView::mouse_traits::on_down_type{});
  v.event(SpecificView::mouse_traits::on_drag_type{});
  v.event(SpecificView::mouse_traits::on_over_type{});
  v.event(SpecificView::mouse_traits::on_up_type{});
  v.event(SpecificView::mouse_traits::on_out_type{});
  v.event(SpecificView::mouse_traits::on_double_click_type{});

  // sub case
  v.add_sub_view(usagi::ui::base_view<float, DrawContext, MouseParameter>{});
  v.event(SpecificView::mouse_traits::on_down_type{});
  v.event(SpecificView::mouse_traits::on_drag_type{});
  v.event(SpecificView::mouse_traits::on_over_type{});
  v.event(SpecificView::mouse_traits::on_up_type{});
  v.event(SpecificView::mouse_traits::on_out_type{});
  v.event(SpecificView::mouse_traits::on_double_click_type{});
}

TEST(ViewCommonTest, MakeCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  ASSERT_TRUE(static_cast<bool>(v));
}
