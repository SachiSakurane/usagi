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

class CountingView final : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {
public:
  using base_view_type = usagi::ui::base_view<float, DrawContext, GestureParameterType>;
  using gesture_traits = typename base_view_type::gesture_traits;
  using offset_type = typename base_view_type::offset_type;

  CountingView(int &d, int &o, int &out, const rect_type &frame)
      : base_view_type{frame}, downs{d}, overs{o}, outs{out} {}

  bool event(typename gesture_traits::on_down_type, offset_type) override {
    downs += 1;
    return true;
  }

  bool event(typename gesture_traits::on_over_type, offset_type) override {
    overs += 1;
    return true;
  }

  void event(typename gesture_traits::on_out_type, offset_type) override { outs += 1; }

  using base_view_type::event;

private:
  int &downs;
  int &overs;
  int &outs;
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

TEST(ViewStackTest, ClipsNewHitEventsToOwnBoundsByDefault) {
  auto downs = 0;
  auto overs = 0;
  auto outs = 0;
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  stack.add_child_view(usagi::ui::make_view<CountingView>(
      downs, overs, outs, usagi::geometry::rect<float>{20.f, 20.f, 40.f, 40.f}));

  const auto consumed =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                      usagi::geometry::point<float>{25.f, 25.f}, 0.f, true, false, false, false,
                      false},
                  typename CountingView::offset_type{});

  ASSERT_FALSE(consumed);
  ASSERT_EQ(downs, 0);
  ASSERT_TRUE(stack.is_event_clipping());
}

TEST(ViewStackTest, CanDispatchNewHitEventsOutsideOwnBounds) {
  auto downs = 0;
  auto overs = 0;
  auto outs = 0;
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  stack.set_event_clipping(false);
  stack.add_child_view(usagi::ui::make_view<CountingView>(
      downs, overs, outs, usagi::geometry::rect<float>{20.f, 20.f, 40.f, 40.f}));

  const auto consumed =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                      usagi::geometry::point<float>{25.f, 25.f}, 0.f, true, false, false, false,
                      false},
                  typename CountingView::offset_type{});

  ASSERT_TRUE(consumed);
  ASSERT_EQ(downs, 1);
  ASSERT_FALSE(stack.is_event_clipping());
}

TEST(ViewStackTest, ClearsOveredChildWhenOverEventIsClipped) {
  auto downs = 0;
  auto overs = 0;
  auto outs = 0;
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  auto &entry = stack.add_child_view(usagi::ui::make_view<CountingView>(
      downs, overs, outs, usagi::geometry::rect<float>{2.f, 2.f, 8.f, 8.f}));

  const auto consumed =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_over_type{
                      usagi::geometry::point<float>{4.f, 4.f}, 0.f, false, false, false, false,
                      false},
                  typename CountingView::offset_type{});

  ASSERT_TRUE(consumed);
  ASSERT_EQ(overs, 1);
  ASSERT_TRUE(entry.second.is_overed());

  const auto clipped =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_over_type{
                      usagi::geometry::point<float>{20.f, 20.f}, 0.f, false, false, false, false,
                      false},
                  typename CountingView::offset_type{});

  ASSERT_FALSE(clipped);
  ASSERT_EQ(outs, 1);
  ASSERT_FALSE(entry.second.is_overed());
}
