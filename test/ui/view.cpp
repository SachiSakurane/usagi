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

TEST(ViewTest, BoundsCase) {
  auto v = usagi::ui::view{usagi::ui::base_view<float, DrawContext, MouseParameter>{
      usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}}};
  ASSERT_EQ(v.bounds(), (usagi::geometry::size<float>{30.f, 30.f}));
  ASSERT_EQ(v.frame(), (usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}));
}

TEST(ViewTest, PredicationCase) {
  {
    auto v = usagi::ui::view<float, DrawContext, MouseParameter>{};
    ASSERT_FALSE(static_cast<bool>(v));
  }
  {
    auto v = usagi::ui::view{SpecificView{}};
    ASSERT_TRUE(static_cast<bool>(v));
  }
}

TEST(ViewTest, DrawCase) {
  auto v = usagi::ui::view{SpecificView{}};
  auto context = DrawContext{};
  v.draw(context);

  // sub case
  v.add_sub_view(usagi::ui::base_view<float, DrawContext, MouseParameter>{});
  v.draw(context);
}

TEST(ViewTest, SubViewCase) {
  auto v = usagi::ui::view{SpecificView{}};

  ASSERT_FALSE(v.remove_sub_view(0));

  {
    auto& sub = v.add_sub_view(SpecificView{});
    ASSERT_TRUE(static_cast<bool>(sub));
  }
  ASSERT_EQ(v.sub_view_size(), 1);

  v.add_sub_view(usagi::ui::base_view<float, DrawContext, MouseParameter>{});
  ASSERT_EQ(v.sub_view_size(), 2);

  ASSERT_TRUE(v.remove_sub_view(1));
  ASSERT_EQ(v.sub_view_size(), 1);

  ASSERT_TRUE(v.remove_sub_view(0));
  ASSERT_EQ(v.sub_view_size(), 0);

  ASSERT_FALSE(v.remove_sub_view(0));
}

TEST(ViewTest, ClickCase) {
  auto v = usagi::ui::view{SpecificView{}};
  v.event(SpecificView::mouse_traits::on_down_type{});
  v.event(SpecificView::mouse_traits::on_drag_type{});
  v.event(SpecificView::mouse_traits::on_over_type{});
  v.event(SpecificView::mouse_traits::on_up_type{});
  v.event(SpecificView::mouse_traits::on_out_type{});

  // sub case
  v.add_sub_view(usagi::ui::base_view<float, DrawContext, MouseParameter>{});
  v.event(SpecificView::mouse_traits::on_down_type{});
  v.event(SpecificView::mouse_traits::on_drag_type{});
  v.event(SpecificView::mouse_traits::on_over_type{});
  v.event(SpecificView::mouse_traits::on_up_type{});
  v.event(SpecificView::mouse_traits::on_out_type{});
}

TEST(ViewTest, MakeCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  ASSERT_TRUE(static_cast<bool>(v));
}
