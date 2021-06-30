#pragma once

#include <usagi/geometry/geometry_traits.h>
#include <usagi/type/mouse.h>
#include <usagi/ui/view.h>
#include <usagi/wrapper/icontrol/draw_context.h>

namespace usagi::wrapper::icontrol
{
  struct iplug_traits
  {
    using value_type = float;
    using mouse_traits = typename usagi::type::mouse_traits<value_type>;
    using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
    using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
    using draw_context_type = typename usagi::wrapper::icontrol::draw_context<value_type, IGraphics>;
    using view_type = typename usagi::ui::view<value_type, draw_context_type>;
  };

  class view_wrapper : public IControl
  {
  public:
    view_wrapper(const IRECT &bounds)
        : IControl{bounds},
          local_view{
              usagi::ui::base_view<iplug_traits::value_type, iplug_traits::draw_context_type>{
                  iplug_traits::point_type{bounds.L, bounds.T},
                  iplug_traits::size_type{bounds.W(), bounds.H()}}}
    {
    }

    void Draw(IGraphics &g) override
    {
      iplug_traits::draw_context_type context{g};
      local_view.draw(context);
    }

    void OnMouseDown(float x, float y, const IMouseMod &mod) override
    {
      local_view.event(iplug_traits::mouse_traits::on_down_type{x, y});
    }

    void OnMouseDrag(float x, float y, float dX, float dY, const IMouseMod &mod) override
    {
      local_view.event(iplug_traits::mouse_traits::on_drag_type{x, y});
    }

    void OnMouseUp(float x, float y, const IMouseMod &mod) override
    {
      local_view.event(iplug_traits::mouse_traits::on_up_type{x, y});
    }

    void OnMouseOver(float x, float y, const IMouseMod &mod) override
    {
      local_view.event(iplug_traits::mouse_traits::on_over_type{x, y});
    }

  private:
    iplug_traits::view_type local_view;
  };
}
