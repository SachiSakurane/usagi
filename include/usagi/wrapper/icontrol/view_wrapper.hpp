#pragma once

#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/type/mouse.hpp>
#include <usagi/ui/view.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::wrapper::icontrol {
template <usagi::utility::arithmetic ValueType>
struct iplug_mouse_parameter {
  ValueType x, y;
  // update mouse pointer
  IGraphics *graphics;
};

struct iplug_traits {
  using value_type = float;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using draw_context_type = SkCanvas;
  using mouse_parameter_type = iplug_mouse_parameter<value_type>;
  using mouse_traits = typename usagi::type::mouse_traits<mouse_parameter_type>;
  using view_type = typename usagi::ui::view<value_type, draw_context_type, mouse_parameter_type>;
  using base_view_type =
      typename usagi::ui::base_view<value_type, draw_context_type, mouse_parameter_type>;
};

class view_wrapper : public IControl {
public:
  explicit view_wrapper(const IRECT &bounds)
      : IControl{bounds}, local_rect{bounds},
        wrapped_bounds{
            usagi::geometry::tupled_rect<iplug_traits::value_type>{[&rect = this->local_rect]() {
              return std::make_tuple(rect.L, rect.T, rect.R, rect.B);
            }}},
        local_view{iplug_traits::base_view_type{wrapped_bounds}} {}

  void set_double_click_enabled(bool flag) { mDblAsSingleClick = !flag; }

  // IControl
  void Draw(IGraphics &g) override {
    SkCanvas *canvas = static_cast<SkCanvas *>(g.GetDrawContext());
    if (canvas) {
      local_view.draw(*canvas);
    }
  }

  void OnResize() override { local_rect = GetRECT(); }

  void OnMouseDown(float x, float y, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_down_type{x, y, GetUI()});
    IControl::OnMouseDown(x, y, mod);
  }

  void OnMouseDrag(float x, float y, float dX, float dY, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_drag_type{x, y, GetUI()});
    IControl::OnMouseDrag(x, y, dX, dY, mod);
  }

  void OnMouseUp(float x, float y, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_up_type{x, y, GetUI()});
    IControl::OnMouseUp(x, y, mod);
  }

  void OnMouseOver(float x, float y, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_over_type{x, y, GetUI()});
    IControl::OnMouseOver(x, y, mod);
  }

  void OnMouseOut() override {
    local_view.event(iplug_traits::mouse_traits::on_out_type{0.f, 0.f, GetUI()});
    IControl::OnMouseOut();
  }

  void OnMouseDblClick(float x, float y, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_double_click_type{x, y, GetUI()});
    IControl::OnMouseDblClick(x, y, mod);
  }

protected:
  IRECT local_rect;
  iplug_traits::rect_type wrapped_bounds;
  iplug_traits::view_type local_view;
};
} // namespace usagi::wrapper::icontrol
