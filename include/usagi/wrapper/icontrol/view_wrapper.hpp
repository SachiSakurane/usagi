#pragma once

#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/type/mouse.hpp>
#include <usagi/ui/view.hpp>

namespace usagi::wrapper::icontrol {
struct iplug_traits {
  using value_type = float;
  using mouse_traits = typename usagi::type::mouse_traits<value_type>;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using draw_context_type = SkCanvas;
  using view_type = typename usagi::ui::view<value_type, draw_context_type>;
  using base_view_type = typename usagi::ui::base_view<value_type, draw_context_type>;
};

class view_wrapper : public IControl {
public:
  view_wrapper(const IRECT &bounds)
      : IControl{bounds}, local_view{iplug_traits::base_view_type{iplug_traits::rect_type{
                              iplug_traits::point_type{bounds.L, bounds.T},
                              iplug_traits::size_type{bounds.W(), bounds.H()}}}} {}

  void Draw(IGraphics &g) override {
    SkCanvas *canvas = static_cast<SkCanvas *>(g.GetDrawContext());
    if (canvas) {
      local_view.draw(*canvas);
    }
  }

  void OnMouseDown(float x, float y, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_down_type{x, y});
  }

  void OnMouseDrag(float x, float y, float dX, float dY, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_drag_type{x, y});
  }

  void OnMouseUp(float x, float y, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_up_type{x, y});
  }

  void OnMouseOver(float x, float y, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_over_type{x, y});
  }

protected:
  iplug_traits::view_type local_view;
};
} // namespace usagi::wrapper::icontrol
