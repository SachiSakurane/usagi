#include <usagi/concepts/ui/layered.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/layered.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_parameter<float>;
using BaseView = usagi::ui::base_view<float, DrawContext, GestureParameterType>;

static_assert(usagi::concepts::ui::layered<usagi::ui::layer<BaseView>>);
static_assert(usagi::concepts::ui::viewable<usagi::ui::layer<BaseView>>);
} // namespace
