#include <usagi/ui/base_view.hpp>
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

static_assert(std::is_same_v<decltype(usagi::ui::detail::pick_handler_wrapper<
                                      usagi::ui::detail::on_drag_tag>(
                                  usagi::ui::on_down(
                                      [](View::gesture_traits::on_down_type, View::offset_type,
                                         View &) { return true; }))),
                             std::nullptr_t>);

} // namespace
