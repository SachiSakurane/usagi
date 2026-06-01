#include <usagi/concepts/ui/view_container.hpp>
#include <usagi/ui/view_stack.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_parameter<float>;
using ViewStack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>;

static_assert(usagi::concepts::ui::view_container<ViewStack>);
static_assert(usagi::concepts::ui::viewable<ViewStack>);
} // namespace
