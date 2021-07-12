#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/view.hpp>

struct DrawContextable {
  using draw_type = std::function<void()>;
  void draw(draw_type &&d) const;
};

class SpecialView final : public usagi::ui::base_view<float, DrawContextable> {};

// static test
namespace {
static_assert(usagi::concepts::ui::viewable<usagi::ui::view<float, DrawContextable>>,
              "usagi::ui::view<float, DrawContextable> has viewable concept");
static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{SpecialView{}})>,
              "view is constructable from SpecialView");
static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{(SpecialView{})})>,
              "view is constructable from SpecialView");
} // namespace

TEST(ViewTest, BoundsCase) {
  auto v = usagi::ui::view{usagi::ui::base_view<float, DrawContextable>{
      usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}}};
  ASSERT_EQ(v.bounds(), (usagi::geometry::size<float>{30.f, 30.f}));
  ASSERT_EQ(v.frame(), (usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f}));
}

TEST(ViewTest, PredicationCase) {
  {
    auto v = usagi::ui::view<float, DrawContextable>{};
    ASSERT_FALSE(static_cast<bool>(v));
  }
  {
    auto v = usagi::ui::view{SpecialView{}};
    ASSERT_TRUE(static_cast<bool>(v));
  }
}

TEST(ViewTest, DrawCase) {
  auto v = usagi::ui::view{SpecialView{}};
  auto context = DrawContextable{};
  v.draw(context);

  // sub case
  v.add_sub_view(usagi::ui::base_view<float, DrawContextable>{});
  v.draw(context);
}

TEST(ViewTest, SubViewCase) {
  auto v = usagi::ui::view{SpecialView{}};
  auto &sub = v.add_sub_view(usagi::ui::base_view<float, DrawContextable>{});
  ASSERT_TRUE(static_cast<bool>(sub));
}

TEST(ViewTest, ClickCase) {
  auto v = usagi::ui::view{SpecialView{}};
  v.event(usagi::type::mouse_traits<float>::on_down_type{});
  v.event(usagi::type::mouse_traits<float>::on_drag_type{});
  v.event(usagi::type::mouse_traits<float>::on_over_type{});
  v.event(usagi::type::mouse_traits<float>::on_up_type{});

  // sub case
  v.add_sub_view(usagi::ui::base_view<float, DrawContextable>{});
  v.event(usagi::type::mouse_traits<float>::on_down_type{});
  v.event(usagi::type::mouse_traits<float>::on_drag_type{});
  v.event(usagi::type::mouse_traits<float>::on_over_type{});
  v.event(usagi::type::mouse_traits<float>::on_up_type{});
}

TEST(ViewTest, MakeCase) {
  auto v = usagi::ui::make_view<SpecialView>();
  ASSERT_TRUE(static_cast<bool>(v));
}
