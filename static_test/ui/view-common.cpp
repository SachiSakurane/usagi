#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_default_parameter<float>;
using BaseView = usagi::ui::view<float, DrawContext, GestureParameterType>;

static_assert(usagi::concepts::ui::viewable<BaseView>);
} // namespace
