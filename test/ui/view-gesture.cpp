#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext {};
using MouseParameter = usagi::type::gesture_default_parameter<float>;
class SpecificView final : public usagi::ui::base_view<float, DrawContext, MouseParameter> {};
} // namespace

TEST(ViewGestureTest, MouseCase) {
  auto v = usagi::ui::view{SpecificView{}};
  v.event(SpecificView::mouse_traits::on_down_type{});
  v.event(SpecificView::mouse_traits::on_drag_type{});
  v.event(SpecificView::mouse_traits::on_over_type{});
  v.event(SpecificView::mouse_traits::on_up_type{});
  v.event(SpecificView::mouse_traits::on_out_type{});
  v.event(SpecificView::mouse_traits::on_double_type{});
  v.event(SpecificView::mouse_traits::on_wheel_type{});

  // sub case
  v.add_sub_view(usagi::ui::base_view<float, DrawContext, MouseParameter>{});
  v.event(SpecificView::mouse_traits::on_down_type{});
  v.event(SpecificView::mouse_traits::on_drag_type{});
  v.event(SpecificView::mouse_traits::on_over_type{});
  v.event(SpecificView::mouse_traits::on_up_type{});
  v.event(SpecificView::mouse_traits::on_out_type{});
  v.event(SpecificView::mouse_traits::on_double_type{});
  v.event(SpecificView::mouse_traits::on_wheel_type{});
}