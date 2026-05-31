#include <usagi/concepts/ui/draw_handler.hpp>
#include <usagi/ui/draw_handler.hpp>
#include <usagi/ui/gesture_handler.hpp>
#include <usagi/ui/base_view.hpp>

namespace {
struct DrawContext {};
using View = usagi::ui::base_view<float, DrawContext, usagi::type::gesture_parameter<float>>;

static_assert(usagi::concepts::ui::is_draw_handler_v<decltype(usagi::ui::on_draw(
                  [](View::draw_context_type &, View::offset_type, const View &) {}))>);
static_assert(usagi::concepts::ui::draw_handler<decltype(usagi::ui::on_draw(
                  [](View::draw_context_type &, View::offset_type, const View &) {}))>);
static_assert(!usagi::concepts::ui::draw_handler<decltype(usagi::ui::on_down(
                   [](View::gesture_traits::on_down_type, View::offset_type, View &) {
                     return true;
                   }))>);
} // namespace
