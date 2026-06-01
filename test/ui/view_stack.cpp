#include <vector>

#include <gtest/gtest.h>
#include <usagi/geometry/point/operator.hpp>
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

class EventView final : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {
public:
  using base_view_type = usagi::ui::base_view<float, DrawContext, GestureParameterType>;
  using gesture_traits = typename base_view_type::gesture_traits;
  using offset_type = typename base_view_type::offset_type;

  EventView(std::vector<offset_type> &p, std::vector<offset_type> &o, const rect_type &frame)
      : base_view_type{frame}, positions{p}, offsets{o} {}

  bool event(typename gesture_traits::on_down_type parameter, offset_type offset) override {
    positions.emplace_back(parameter.position);
    offsets.emplace_back(offset);
    return true;
  }

  using base_view_type::event;

private:
  std::vector<offset_type> &positions;
  std::vector<offset_type> &offsets;
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

TEST(ViewStackTest, SendsLocalGesturePositionToChild) {
  using point_type = usagi::geometry::point<float>;

  auto positions = std::vector<point_type>{};
  auto offsets = std::vector<point_type>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 100.f, 100.f}};
  stack.add_child_view(
      usagi::ui::make_view<EventView>(positions, offsets,
                                      usagi::geometry::rect<float>{20.f, 30.f, 50.f, 60.f}));

  const auto consumed =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                      point_type{25.f, 35.f}, 0.f, true, false, false, false, false},
                  point_type{100.f, 200.f});

  ASSERT_TRUE(consumed);
  const auto expected_positions = std::vector<point_type>{{5.f, 5.f}};
  const auto expected_offsets = std::vector<point_type>{{120.f, 230.f}};
  ASSERT_EQ(positions, expected_positions);
  ASSERT_EQ(offsets, expected_offsets);
}

TEST(ViewStackTest, BaseViewHitTestUsesLocalGesturePosition) {
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 100.f, 100.f}};
  stack.add_child_view(usagi::ui::make_view<
                       usagi::ui::base_view<float, DrawContext, GestureParameterType>>(
      usagi::geometry::rect<float>{20.f, 30.f, 50.f, 60.f}));

  const auto consumed =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                      usagi::geometry::point<float>{25.f, 35.f}, 0.f, true, false, false, false,
                      false},
                  typename EventView::offset_type{});

  ASSERT_TRUE(consumed);
}
