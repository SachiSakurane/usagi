#include <gtest/gtest.h>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_parameter<float>;
class SpecificView final : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {};
} // namespace

TEST(ViewGestureTest, Case) {
  auto v = usagi::ui::make_view<SpecificView>();
  v.event(SpecificView::gesture_traits::on_down_type{}, typename SpecificView::offset_type{});
  v.event(SpecificView::gesture_traits::on_drag_type{}, typename SpecificView::offset_type{});
  v.event(SpecificView::gesture_traits::on_over_type{}, typename SpecificView::offset_type{});
  v.event(SpecificView::gesture_traits::on_up_type{}, typename SpecificView::offset_type{});
  v.event(SpecificView::gesture_traits::on_out_type{}, typename SpecificView::offset_type{});
  v.event(SpecificView::gesture_traits::on_double_type{}, typename SpecificView::offset_type{});
  v.event(SpecificView::gesture_traits::on_wheel_type{}, typename SpecificView::offset_type{});
}