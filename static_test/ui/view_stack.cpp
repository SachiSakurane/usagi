#include <usagi/concepts/ui/view_container.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/view_stack.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_parameter<float>;
using BaseView = usagi::ui::base_view<float, DrawContext, GestureParameterType>;

static_assert(usagi::concepts::ui::view_container<usagi::ui::view_stack<BaseView>>);
static_assert(usagi::concepts::ui::viewable<usagi::ui::view_stack<BaseView>>);
} // namespace
