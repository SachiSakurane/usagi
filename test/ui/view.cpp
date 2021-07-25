#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/view.hpp>

struct DrawContext {};

class SpecificView final : public usagi::ui::base_view<float, DrawContext> {};

// static test
namespace {
static_assert(usagi::concepts::ui::viewable<usagi::ui::view<float, DrawContext>>,
              "usagi::ui::view<float, DrawContextable> has viewable concept");
static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{SpecificView{}})>,
              "view is constructable from SpecificView");
static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{(SpecificView{})})>,
              "view is constructable from SpecificView");
} // namespace

TEST(ViewTest, BoundsCase) {
  auto v = usagi::ui::view{usagi::ui::base_view<float, DrawContext>{
      usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}}};
  ASSERT_EQ(v.bounds(), (usagi::geometry::size<float>{30.f, 30.f}));
  ASSERT_EQ(v.frame(), (usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}));
}

TEST(ViewTest, PredicationCase) {
  {
    auto v = usagi::ui::view<float, DrawContext>{};
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
  v.add_sub_view(usagi::ui::base_view<float, DrawContext>{});
  v.draw(context);
}

TEST(ViewTest, SubViewCase) {
  auto v = usagi::ui::view{SpecificView{}};
  auto &sub = v.add_sub_view(usagi::ui::base_view<float, DrawContext>{});
  ASSERT_TRUE(static_cast<bool>(sub));
}

TEST(ViewTest, ClickCase) {
  auto v = usagi::ui::view{SpecificView{}};
  v.event(usagi::type::mouse_traits<float>::on_down_type{});
  v.event(usagi::type::mouse_traits<float>::on_drag_type{});
  v.event(usagi::type::mouse_traits<float>::on_over_type{});
  v.event(usagi::type::mouse_traits<float>::on_up_type{});

  // sub case
  v.add_sub_view(usagi::ui::base_view<float, DrawContext>{});
  v.event(usagi::type::mouse_traits<float>::on_down_type{});
  v.event(usagi::type::mouse_traits<float>::on_drag_type{});
  v.event(usagi::type::mouse_traits<float>::on_over_type{});
  v.event(usagi::type::mouse_traits<float>::on_up_type{});
}

TEST(ViewTest, MakeCase) {
  auto v = usagi::ui::make_view<SpecificView>();
  ASSERT_TRUE(static_cast<bool>(v));
}
