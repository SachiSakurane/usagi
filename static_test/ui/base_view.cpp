#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/base_view.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_parameter<float>;
using BaseViewType = usagi::ui::base_view<float, DrawContext, GestureParameterType>;

static_assert(usagi::concepts::ui::viewable<BaseViewType>);
static_assert([]() consteval {
  BaseViewType default_construct, rect_construct{BaseViewType::rect_type{}};
  return true;
}());

// drawable
static_assert([]() consteval {
  BaseViewType view;
  DrawContext context;
  view.draw(context, typename BaseViewType::offset_type{});
  return true;
}());

// gestural
// static_assert([]() consteval {
//  using gesture_traits = BaseViewType::gesture_traits;
//  BaseViewType view;
//  view.event(gesture_traits::on_down_type{});
//  return true;
//}());

// viewable
static_assert([]() consteval {
  BaseViewType view{BaseViewType::rect_type{1.f, 1.f, 3.f, 3.f}};

  if (view.bounds() != BaseViewType::size_type{2.f, 2.f}) {
    return false;
  }

  if (view.frame() != BaseViewType::rect_type{1.f, 1.f, 3.f, 3.f}) {
    return false;
  }

  return true;
}());

} // namespace
