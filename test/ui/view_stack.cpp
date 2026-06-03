#include <vector>

#include <gtest/gtest.h>
#include <usagi/geometry/point/operator.hpp>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/view.hpp>
#include <usagi/ui/view_stack.hpp>

namespace {
constexpr auto pi = 3.14159265358979323846f;

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

class OffsetDrawView final : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {
public:
  using base_view_type = usagi::ui::base_view<float, DrawContext, GestureParameterType>;
  using offset_type = typename base_view_type::offset_type;

  OffsetDrawView(std::vector<offset_type> &o, const rect_type &frame)
      : base_view_type{frame}, offsets{o} {}

  void draw(draw_context_type &, offset_type offset) override { offsets.emplace_back(offset); }

private:
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

class DragUpView final : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {
public:
  using base_view_type = usagi::ui::base_view<float, DrawContext, GestureParameterType>;
  using gesture_traits = typename base_view_type::gesture_traits;
  using offset_type = typename base_view_type::offset_type;

  DragUpView(int &d, int &drag, int &u, const rect_type &frame)
      : base_view_type{frame}, downs{d}, drags{drag}, ups{u} {}

  bool event(typename gesture_traits::on_down_type, offset_type) override {
    downs += 1;
    return true;
  }

  void event(typename gesture_traits::on_drag_type, offset_type) override { drags += 1; }

  void event(typename gesture_traits::on_up_type, offset_type) override { ups += 1; }

  using base_view_type::event;

private:
  int &downs;
  int &drags;
  int &ups;
};

class OptionalDragUpView final
    : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {
public:
  using base_view_type = usagi::ui::base_view<float, DrawContext, GestureParameterType>;
  using gesture_traits = typename base_view_type::gesture_traits;
  using offset_type = typename base_view_type::offset_type;

  OptionalDragUpView(int &d, int &drag, int &u, bool consume, const rect_type &frame)
      : base_view_type{frame}, downs{d}, drags{drag}, ups{u}, consumes_down{consume} {}

  bool event(typename gesture_traits::on_down_type, offset_type) override {
    downs += 1;
    return consumes_down;
  }

  void event(typename gesture_traits::on_drag_type, offset_type) override { drags += 1; }

  void event(typename gesture_traits::on_up_type, offset_type) override { ups += 1; }

  using base_view_type::event;

private:
  int &downs;
  int &drags;
  int &ups;
  bool consumes_down;
};

class OptionalOverView final
    : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {
public:
  using base_view_type = usagi::ui::base_view<float, DrawContext, GestureParameterType>;
  using gesture_traits = typename base_view_type::gesture_traits;
  using offset_type = typename base_view_type::offset_type;

  OptionalOverView(int &o, int &out, bool consume, const rect_type &frame)
      : base_view_type{frame}, overs{o}, outs{out}, consumes_over{consume} {}

  bool event(typename gesture_traits::on_over_type, offset_type) override {
    overs += 1;
    return consumes_over;
  }

  void event(typename gesture_traits::on_out_type, offset_type) override { outs += 1; }

  using base_view_type::event;

private:
  int &overs;
  int &outs;
  bool consumes_over;
};

class OrderedView final : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {
public:
  using base_view_type = usagi::ui::base_view<float, DrawContext, GestureParameterType>;
  using gesture_traits = typename base_view_type::gesture_traits;
  using offset_type = typename base_view_type::offset_type;

  OrderedView(std::vector<int> &s, int id, const rect_type &frame)
      : base_view_type{frame}, stamp{s}, value{id} {}

  void draw(draw_context_type &, offset_type) override { stamp.emplace_back(value); }

  bool event(typename gesture_traits::on_down_type, offset_type) override {
    stamp.emplace_back(value);
    return true;
  }

  using base_view_type::event;

private:
  std::vector<int> &stamp;
  int value;
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

TEST(ViewStackTest, SendsTranslatedLocalGesturePositionToChild) {
  using point_type = usagi::geometry::point<float>;

  auto positions = std::vector<point_type>{};
  auto offsets = std::vector<point_type>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 100.f, 100.f}};
  const auto key = stack.add_child_view(
      usagi::ui::make_view<EventView>(positions, offsets,
                                      usagi::geometry::rect<float>{20.f, 30.f, 50.f, 60.f}));
  stack.get_child_view(key).set_translation(point_type{10.f, 20.f});

  const auto misses_layout_position =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                      point_type{25.f, 35.f}, 0.f, true, false, false, false, false},
                  point_type{100.f, 200.f});

  ASSERT_FALSE(misses_layout_position);
  ASSERT_TRUE(positions.empty());
  ASSERT_TRUE(offsets.empty());

  const auto consumed =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                      point_type{35.f, 55.f}, 0.f, true, false, false, false, false},
                  point_type{100.f, 200.f});

  ASSERT_TRUE(consumed);
  const auto expected_positions = std::vector<point_type>{{5.f, 5.f}};
  const auto expected_offsets = std::vector<point_type>{{130.f, 250.f}};
  ASSERT_EQ(positions, expected_positions);
  ASSERT_EQ(offsets, expected_offsets);
}

TEST(ViewStackTest, SendsScaledLocalGesturePositionToChild) {
  using point_type = usagi::geometry::point<float>;

  auto positions = std::vector<point_type>{};
  auto offsets = std::vector<point_type>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 100.f, 100.f}};
  const auto key = stack.add_child_view(
      usagi::ui::make_view<EventView>(positions, offsets,
                                      usagi::geometry::rect<float>{20.f, 30.f, 50.f, 60.f}));
  auto &child = stack.get_child_view(key);
  child.set_translation(point_type{10.f, 20.f});
  child.set_scale(point_type{2.f, 2.f}, point_type{0.f, 0.f});

  const auto consumed =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                      point_type{40.f, 60.f}, 0.f, true, false, false, false, false},
                  point_type{100.f, 200.f});

  ASSERT_TRUE(consumed);
  const auto expected_positions = std::vector<point_type>{{5.f, 5.f}};
  const auto expected_offsets = std::vector<point_type>{{130.f, 250.f}};
  ASSERT_EQ(positions, expected_positions);
  ASSERT_EQ(offsets, expected_offsets);
}

TEST(ViewStackTest, HitTestUsesScaleOrigin) {
  using point_type = usagi::geometry::point<float>;

  auto positions = std::vector<point_type>{};
  auto offsets = std::vector<point_type>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 100.f, 100.f}};
  const auto key = stack.add_child_view(
      usagi::ui::make_view<EventView>(positions, offsets,
                                      usagi::geometry::rect<float>{20.f, 30.f, 50.f, 60.f}));
  stack.get_child_view(key).set_scale(point_type{2.f, 2.f}, point_type{10.f, 10.f});

  const auto consumed =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                      point_type{10.f, 20.f}, 0.f, true, false, false, false, false},
                  point_type{100.f, 200.f});

  ASSERT_TRUE(consumed);
  const auto expected_positions = std::vector<point_type>{{0.f, 0.f}};
  const auto expected_offsets = std::vector<point_type>{{120.f, 230.f}};
  ASSERT_EQ(positions, expected_positions);
  ASSERT_EQ(offsets, expected_offsets);
}

TEST(ViewStackTest, SendsRotatedLocalGesturePositionToChild) {
  using point_type = usagi::geometry::point<float>;

  auto positions = std::vector<point_type>{};
  auto offsets = std::vector<point_type>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 100.f, 100.f}};
  const auto key = stack.add_child_view(
      usagi::ui::make_view<EventView>(positions, offsets,
                                      usagi::geometry::rect<float>{20.f, 30.f, 50.f, 60.f}));
  stack.get_child_view(key).set_rotation(pi / 2.f);

  const auto consumed =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                      point_type{15.f, 35.f}, 0.f, true, false, false, false, false},
                  point_type{100.f, 200.f});

  ASSERT_TRUE(consumed);
  ASSERT_EQ(positions.size(), 1u);
  EXPECT_NEAR(positions.front().x(), 5.f, 0.0001f);
  EXPECT_NEAR(positions.front().y(), 5.f, 0.0001f);
  const auto expected_offsets = std::vector<point_type>{{120.f, 230.f}};
  ASSERT_EQ(offsets, expected_offsets);
}

TEST(ViewStackTest, HitTestUsesRotationOrigin) {
  using point_type = usagi::geometry::point<float>;

  auto positions = std::vector<point_type>{};
  auto offsets = std::vector<point_type>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 100.f, 100.f}};
  const auto key = stack.add_child_view(
      usagi::ui::make_view<EventView>(positions, offsets,
                                      usagi::geometry::rect<float>{20.f, 30.f, 50.f, 60.f}));
  stack.get_child_view(key).set_rotation(pi / 2.f, point_type{10.f, 10.f});

  const auto consumed =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                      point_type{40.f, 30.f}, 0.f, true, false, false, false, false},
                  point_type{100.f, 200.f});

  ASSERT_TRUE(consumed);
  ASSERT_EQ(positions.size(), 1u);
  EXPECT_NEAR(positions.front().x(), 0.f, 0.0001f);
  EXPECT_NEAR(positions.front().y(), 0.f, 0.0001f);
  const auto expected_offsets = std::vector<point_type>{{120.f, 230.f}};
  ASSERT_EQ(offsets, expected_offsets);
}

TEST(ViewStackTest, DrawOffsetIncludesChildTranslation) {
  using point_type = usagi::geometry::point<float>;

  auto offsets = std::vector<point_type>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 100.f, 100.f}};
  const auto key = stack.add_child_view(usagi::ui::make_view<OffsetDrawView>(
      offsets, usagi::geometry::rect<float>{20.f, 30.f, 50.f, 60.f}));
  stack.get_child_view(key).set_translation(point_type{10.f, 20.f});

  auto context = DrawContext{};
  stack.draw(context, point_type{100.f, 200.f});

  const auto expected_offsets = std::vector<point_type>{{130.f, 250.f}};
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
  const auto key = stack.add_child_view(usagi::ui::make_view<CountingView>(
      downs, overs, outs, usagi::geometry::rect<float>{2.f, 2.f, 8.f, 8.f}));

  const auto consumed =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_over_type{
                      usagi::geometry::point<float>{4.f, 4.f}, 0.f, false, false, false, false,
                      false},
                  typename CountingView::offset_type{});

  ASSERT_TRUE(consumed);
  ASSERT_EQ(overs, 1);
  ASSERT_TRUE(stack.get_child_view(key).is_overed());

  const auto clipped =
      stack.event(usagi::type::gesture_traits<GestureParameterType>::on_over_type{
                      usagi::geometry::point<float>{20.f, 20.f}, 0.f, false, false, false, false,
                      false},
                  typename CountingView::offset_type{});

  ASSERT_FALSE(clipped);
  ASSERT_EQ(outs, 1);
  ASSERT_FALSE(stack.get_child_view(key).is_overed());
}

TEST(ViewStackTest, DrawsChildrenInZOrder) {
  auto stamp = std::vector<int>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  const auto back = stack.add_child_view(usagi::ui::make_view<OrderedView>(
      stamp, 1, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));
  const auto front = stack.add_child_view(usagi::ui::make_view<OrderedView>(
      stamp, 2, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));

  auto context = DrawContext{};
  stack.draw(context, typename OrderedView::offset_type{});
  ASSERT_EQ(stamp, (std::vector<int>{1, 2}));

  stamp.clear();
  ASSERT_TRUE(stack.bring_child_to_front(back));
  stack.draw(context, typename OrderedView::offset_type{});
  ASSERT_EQ(stamp, (std::vector<int>{2, 1}));

  stamp.clear();
  ASSERT_TRUE(stack.send_child_to_back(front));
  stack.draw(context, typename OrderedView::offset_type{});
  ASSERT_EQ(stamp, (std::vector<int>{2, 1}));
}

TEST(ViewStackTest, SendsEventsFromFrontToBack) {
  auto stamp = std::vector<int>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  const auto back = stack.add_child_view(usagi::ui::make_view<OrderedView>(
      stamp, 1, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));
  const auto front = stack.add_child_view(usagi::ui::make_view<OrderedView>(
      stamp, 2, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));

  const auto event = usagi::type::gesture_traits<GestureParameterType>::on_down_type{
      usagi::geometry::point<float>{5.f, 5.f}, 0.f, true, false, false, false, false};

  ASSERT_TRUE(stack.event(event, typename OrderedView::offset_type{}));
  ASSERT_EQ(stamp, (std::vector<int>{2}));

  stamp.clear();
  ASSERT_TRUE(stack.bring_child_to_front(back));
  ASSERT_TRUE(stack.event(event, typename OrderedView::offset_type{}));
  ASSERT_EQ(stamp, (std::vector<int>{1}));

  ASSERT_FALSE(stack.bring_child_to_front(999));
  ASSERT_FALSE(stack.send_child_to_back(999));
}

TEST(ViewStackTest, RemovesChildFromZOrder) {
  auto stamp = std::vector<int>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  const auto first = stack.add_child_view(usagi::ui::make_view<OrderedView>(
      stamp, 1, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));
  stack.add_child_view(usagi::ui::make_view<OrderedView>(
      stamp, 2, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));

  ASSERT_TRUE(stack.remove_child_view(first));
  auto context = DrawContext{};
  stack.draw(context, typename OrderedView::offset_type{});
  ASSERT_EQ(stamp, (std::vector<int>{2}));
}

TEST(ViewStackTest, DragAndUpAreNotClippedAfterDown) {
  auto downs = 0;
  auto drags = 0;
  auto ups = 0;
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  stack.add_child_view(usagi::ui::make_view<DragUpView>(
      downs, drags, ups, usagi::geometry::rect<float>{2.f, 2.f, 8.f, 8.f}));

  ASSERT_TRUE(stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                              usagi::geometry::point<float>{4.f, 4.f}, 0.f, true, false, false,
                              false, false},
                          typename DragUpView::offset_type{}));

  stack.event(usagi::type::gesture_traits<GestureParameterType>::on_drag_type{
                  usagi::geometry::point<float>{20.f, 20.f}, 0.f, true, false, false, false,
                  false},
              typename DragUpView::offset_type{});
  stack.event(usagi::type::gesture_traits<GestureParameterType>::on_up_type{
                  usagi::geometry::point<float>{20.f, 20.f}, 0.f, true, false, false, false,
                  false},
              typename DragUpView::offset_type{});

  ASSERT_EQ(downs, 1);
  ASSERT_EQ(drags, 1);
  ASSERT_EQ(ups, 1);
}

TEST(ViewStackTest, NonConsumingDownChildDoesNotReceiveDragOrUp) {
  auto front_downs = 0;
  auto front_drags = 0;
  auto front_ups = 0;
  auto back_downs = 0;
  auto back_drags = 0;
  auto back_ups = 0;
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  stack.add_child_view(usagi::ui::make_view<OptionalDragUpView>(
      back_downs, back_drags, back_ups, true,
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));
  stack.add_child_view(usagi::ui::make_view<OptionalDragUpView>(
      front_downs, front_drags, front_ups, false,
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));

  ASSERT_TRUE(stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                              usagi::geometry::point<float>{5.f, 5.f}, 0.f, true, false, false,
                              false, false},
                          typename OptionalDragUpView::offset_type{}));

  stack.event(usagi::type::gesture_traits<GestureParameterType>::on_drag_type{
                  usagi::geometry::point<float>{6.f, 6.f}, 0.f, true, false, false, false,
                  false},
              typename OptionalDragUpView::offset_type{});
  stack.event(usagi::type::gesture_traits<GestureParameterType>::on_up_type{
                  usagi::geometry::point<float>{6.f, 6.f}, 0.f, true, false, false, false,
                  false},
              typename OptionalDragUpView::offset_type{});

  ASSERT_EQ(front_downs, 1);
  ASSERT_EQ(back_downs, 1);
  ASSERT_EQ(front_drags, 0);
  ASSERT_EQ(front_ups, 0);
  ASSERT_EQ(back_drags, 1);
  ASSERT_EQ(back_ups, 1);
}

TEST(ViewStackTest, NonConsumingOverChildDoesNotReceiveOut) {
  auto front_overs = 0;
  auto front_outs = 0;
  auto back_overs = 0;
  auto back_outs = 0;
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  stack.add_child_view(usagi::ui::make_view<OptionalOverView>(
      back_overs, back_outs, true, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));
  stack.add_child_view(usagi::ui::make_view<OptionalOverView>(
      front_overs, front_outs, false, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));

  ASSERT_TRUE(stack.event(usagi::type::gesture_traits<GestureParameterType>::on_over_type{
                              usagi::geometry::point<float>{5.f, 5.f}, 0.f, false, false, false,
                              false, false},
                          typename OptionalOverView::offset_type{}));

  ASSERT_FALSE(stack.event(usagi::type::gesture_traits<GestureParameterType>::on_over_type{
                               usagi::geometry::point<float>{20.f, 20.f}, 0.f, false, false,
                               false, false, false},
                           typename OptionalOverView::offset_type{}));

  ASSERT_EQ(front_overs, 1);
  ASSERT_EQ(back_overs, 1);
  ASSERT_EQ(front_outs, 0);
  ASSERT_EQ(back_outs, 1);
}

TEST(ViewStackTest, OutDispatchesOnlyToOveredChildren) {
  auto front_overs = 0;
  auto front_outs = 0;
  auto back_overs = 0;
  auto back_outs = 0;
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  stack.add_child_view(usagi::ui::make_view<OptionalOverView>(
      back_overs, back_outs, false, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));
  stack.add_child_view(usagi::ui::make_view<OptionalOverView>(
      front_overs, front_outs, true, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));

  ASSERT_TRUE(stack.event(usagi::type::gesture_traits<GestureParameterType>::on_over_type{
                              usagi::geometry::point<float>{5.f, 5.f}, 0.f, false, false, false,
                              false, false},
                          typename OptionalOverView::offset_type{}));

  stack.event(usagi::type::gesture_traits<GestureParameterType>::on_out_type{
                  usagi::geometry::point<float>{20.f, 20.f}, 0.f, false, false, false, false,
                  false},
              typename OptionalOverView::offset_type{});

  ASSERT_EQ(front_overs, 1);
  ASSERT_EQ(back_overs, 0);
  ASSERT_EQ(front_outs, 1);
  ASSERT_EQ(back_outs, 0);
}

TEST(ViewStackTest, DisabledChildIsNotDrawnOrHit) {
  auto stamp = std::vector<int>{};
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  const auto key = stack.add_child_view(usagi::ui::make_view<OrderedView>(
      stamp, 1, usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}));
  stack.get_child_view(key).set_enabled(false);

  auto context = DrawContext{};
  stack.draw(context, typename OrderedView::offset_type{});
  ASSERT_TRUE(stamp.empty());

  ASSERT_FALSE(stack.event(usagi::type::gesture_traits<GestureParameterType>::on_down_type{
                               usagi::geometry::point<float>{5.f, 5.f}, 0.f, true, false, false,
                               false, false},
                           typename OrderedView::offset_type{}));
  ASSERT_TRUE(stamp.empty());
}

TEST(ViewStackTest, RemoveChildViewDoesNotDispatchSyntheticEvents) {
  auto downs = 0;
  auto overs = 0;
  auto outs = 0;
  auto stack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>{
      usagi::geometry::rect<float>{0.f, 0.f, 10.f, 10.f}};
  const auto key = stack.add_child_view(usagi::ui::make_view<CountingView>(
      downs, overs, outs, usagi::geometry::rect<float>{2.f, 2.f, 8.f, 8.f}));

  ASSERT_TRUE(stack.event(usagi::type::gesture_traits<GestureParameterType>::on_over_type{
                              usagi::geometry::point<float>{4.f, 4.f}, 0.f, false, false, false,
                              false, false},
                          typename CountingView::offset_type{}));
  ASSERT_EQ(overs, 1);
  ASSERT_TRUE(stack.get_child_view(key).is_overed());

  ASSERT_TRUE(stack.remove_child_view(key));
  ASSERT_EQ(outs, 0);
}
