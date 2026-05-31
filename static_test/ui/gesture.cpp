#include <usagi/ui/base_view.hpp>
#include <usagi/ui/draw_handler.hpp>
#include <usagi/concepts/ui/gesture_handler.hpp>
#include <usagi/ui/gesture.hpp>

namespace {
struct DrawContext {};
using View = usagi::ui::base_view<float, DrawContext, usagi::type::gesture_parameter<float>>;

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

} // namespace
