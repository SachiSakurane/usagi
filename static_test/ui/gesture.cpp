#include <usagi/ui/base_view.hpp>
#include <usagi/ui/draw_handler.hpp>
#include <usagi/concepts/ui/gesture_handler.hpp>
#include <usagi/concepts/ui/transformable.hpp>
#include <usagi/ui/gesture.hpp>

namespace {
struct DrawContext {};
using View = usagi::ui::base_view<float, DrawContext, usagi::type::gesture_parameter<float>>;
using Gesture = usagi::ui::gesture<View, std::tuple<>>;

static_assert(usagi::concepts::ui::transformable<Gesture>);

static_assert(usagi::concepts::ui::is_gesture_handler_v<decltype(usagi::ui::on_down(
                  [](View::gesture_traits::on_down_type, View::offset_type, View &) {
                    return true;
                  }))>);

static_assert(usagi::concepts::ui::gesture_tuple_requirement<
              decltype(std::make_tuple(usagi::ui::on_down(
                  [](View::gesture_traits::on_down_type, View::offset_type, View &) {
                    return true;
                  }))),
              View>);

static_assert(!usagi::concepts::ui::gesture_tuple_requirement<
              decltype(std::make_tuple(
                  [](View::gesture_traits::on_down_type, View::offset_type, View &) {
                    return true;
                  })),
              View>);

static_assert(!usagi::concepts::ui::gesture_tuple_requirement<
              decltype(std::make_tuple(usagi::ui::on_down(
                  [](View::gesture_traits::on_drag_type, View::offset_type, View &) {}))),
              View>);

static_assert(!usagi::concepts::ui::gesture_tuple_requirement<
              decltype(std::make_tuple(usagi::ui::on_draw(
                  [](View::draw_context_type &, View::offset_type, const View &) {}))),
              View>);

static_assert([]() consteval {
  auto g = View{} | usagi::ui::gestured();

  g.set_transform(decltype(g)::transform_type{decltype(g)::point_type{1.f, 2.f}, 3.f,
                                              decltype(g)::point_type{4.f, 5.f},
                                              decltype(g)::point_type{6.f, 7.f}});
  if (g.transform().translation() != decltype(g)::point_type{1.f, 2.f}) {
    return false;
  }

  g.set_translation(decltype(g)::point_type{8.f, 9.f});
  g.set_rotation(14.f, decltype(g)::point_type{15.f, 16.f});
  g.set_scale(decltype(g)::point_type{10.f, 11.f}, decltype(g)::point_type{12.f, 13.f});

  return g.translation() == decltype(g)::point_type{8.f, 9.f} &&
      g.rotation() == 14.f &&
      g.scale() == decltype(g)::point_type{10.f, 11.f} &&
      g.transform().origin() == decltype(g)::point_type{12.f, 13.f};
}());

} // namespace
