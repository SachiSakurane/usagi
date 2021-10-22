#pragma once

#include <functional>
#include <unordered_map>

#include <usagi/type/mouse.hpp>
#include <usagi/ui/view.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::wrapper::iplug2 {

struct igraphic_control {
  struct text_entry {
    bool ping;
    std::string value;
  };

  const std::function<void(iplug::igraphics::ECursor)> set_mouse_cursor;
  const std::function<void(bool)> set_mouse_cursor_hidden;
  const std::function<bool(const iplug::igraphics::IText &, const iplug::igraphics::IRECT &,
                           std::string str, const std::weak_ptr<text_entry> &dst)>
      try_create_text_entry;
};

template <usagi::utility::arithmetic ValueType>
struct iplug_mouse_parameter {
  ValueType x, y;
  igraphic_control control;
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
      : IControl{bounds}, local_view{iplug_traits::base_view_type{
                              iplug_traits::rect_type{bounds.L, bounds.T, bounds.R, bounds.B}}} {}

  void set_double_click_enabled(bool flag) { mDblAsSingleClick = !flag; }

  // IControl
  void Draw(IGraphics &g) override {
    SkCanvas *canvas = static_cast<SkCanvas *>(g.GetDrawContext());
    if (canvas) {
      local_view.draw(*canvas);
    }
  }

  void OnMouseDown(float x, float y, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_down_type{x, y, make_igraphic_control()});
    IControl::OnMouseDown(x, y, mod);
  }

  void OnMouseDrag(float x, float y, float dX, float dY, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_drag_type{x, y, make_igraphic_control()});
    IControl::OnMouseDrag(x, y, dX, dY, mod);
  }

  void OnMouseUp(float x, float y, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_up_type{x, y, make_igraphic_control()});
    IControl::OnMouseUp(x, y, mod);
  }

  void OnMouseOver(float x, float y, const IMouseMod &mod) override {
    local_view.event(iplug_traits::mouse_traits::on_over_type{x, y, make_igraphic_control()});
    IControl::OnMouseOver(x, y, mod);
  }

  void OnMouseOut() override {
    local_view.event(iplug_traits::mouse_traits::on_out_type{0.f, 0.f, make_igraphic_control()});
    IControl::OnMouseOut();
  }

  void OnMouseDblClick(float x, float y, const IMouseMod &mod) override {
    local_view.event(
        iplug_traits::mouse_traits::on_double_click_type{x, y, make_igraphic_control()});
    IControl::OnMouseDblClick(x, y, mod);
  }

  void OnTextEntryCompletion(const char *str, int) override {
    if (auto l = text_entry_ptr.lock(); l) {
      l->ping = true;
      l->value = str;
    }
    text_entry_ptr.reset();
  }

protected:
  iplug_traits::view_type local_view;
  std::weak_ptr<igraphic_control::text_entry> text_entry_ptr;

  igraphic_control make_igraphic_control() {
    return igraphic_control{
        .set_mouse_cursor = [this](iplug::igraphics::ECursor c) { GetUI()->SetMouseCursor(c); },
        .set_mouse_cursor_hidden = [this](bool flag) { GetUI()->HideMouseCursor(flag, false); },
        .try_create_text_entry =
            [this](const iplug::igraphics::IText &t, const iplug::igraphics::IRECT &r,
                   std::string src, const std::weak_ptr<igraphic_control::text_entry> &dst) {
              if (text_entry_ptr.expired() && !dst.expired()) {
                GetUI()->CreateTextEntry(*this, t, r, src.c_str());
                text_entry_ptr = dst;
                if (auto l = text_entry_ptr.lock(); l) {
                  l->ping = false;
                  l->value = "";
                }
                return true;
              }
              return false;
            }};
  }
};
} // namespace usagi::wrapper::iplug2
