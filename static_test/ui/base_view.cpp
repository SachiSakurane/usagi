#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/ui/base_view.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_default_parameter<float>;
using BaseViewType = usagi::ui::base_view<float, DrawContext, GestureParameterType>;

static_assert(usagi::concepts::ui::viewable<BaseViewType>);
static_assert([](){
  BaseViewType default_construct, rect_construct{BaseViewType::rect_type{}};
  return true;
}());
} // namespace
