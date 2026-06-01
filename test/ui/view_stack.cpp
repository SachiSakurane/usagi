#include <vector>

#include <gtest/gtest.h>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/view.hpp>
#include <usagi/ui/view_stack.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_parameter<float>;

class DrawnView final : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {
public:
  using base_view_type = usagi::ui::base_view<float, DrawContext, GestureParameterType>;
  using offset_type = typename base_view_type::offset_type;

  DrawnView(std::vector<int> &s, const rect_type &frame) : base_view_type{frame}, stamp{s} {}

  void draw(draw_context_type &, offset_type) override { stamp.emplace_back(1); }

private:
  std::vector<int> &stamp;
};
} // namespace

TEST(ViewStackTest, DrawsOnlyChildren) {
  auto stamp = std::vector<int>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 100.f, 100.f}};

  auto context = DrawContext{};
  stack.draw(context, typename DrawnView::offset_type{});
  ASSERT_TRUE(stamp.empty());

  stack.add_child_view(
      usagi::ui::make_view<DrawnView>(stamp, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));

  stack.draw(context, typename DrawnView::offset_type{});
  ASSERT_EQ(stamp, std::vector<int>{1});
}

TEST(ViewStackTest, OwnsViewState) {
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{10.f, 20.f, 40.f, 60.f}};

  ASSERT_EQ(stack.frame(), (usagi::geometry::rect<float>{10.f, 20.f, 40.f, 60.f}));
  ASSERT_EQ(stack.bounds(), (usagi::geometry::size<float>{30.f, 40.f}));

  ASSERT_TRUE(stack.is_enabled());
  stack.set_enabled(false);
  ASSERT_FALSE(stack.is_enabled());
}
