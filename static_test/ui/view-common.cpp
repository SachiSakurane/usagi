#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_default_parameter<float>;
class SpecificView final : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {};

// static test
static_assert(
    usagi::concepts::ui::viewable<usagi::ui::view<float, DrawContext, GestureParameterType>>,
    "usagi::ui::view<float, DrawContextable> has viewable concept");
static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{SpecificView{}})>,
              "view is constructable from SpecificView");
static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{(SpecificView{})})>,
              "view is constructable from SpecificView");
} // namespace
