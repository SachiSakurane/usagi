#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/geometry/rect/function.hpp>

namespace usagi::ui {
template <usagi::concepts::arithmetic ValueType, class DrawContextType, class GestureParameterType>
class base_view {
public:
  using value_type = ValueType;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = DrawContextType;
  using offset_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using gesture_parameter_type = GestureParameterType;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  base_view() = default;
  constexpr explicit base_view(const usagi::concepts::geometry::rect_concept auto &frame)
      : content{frame} {}

  virtual constexpr ~base_view() = default;

  virtual constexpr void draw(draw_context_type &context, offset_type offset) {}

  virtual bool event(typename gesture_traits::on_down_type g, offset_type offset) {
    if (!ignore_events && usagi::geometry::contain(frame(), g.position)) {
      set_down(true);
      return true;
    }
    return false;
  }
  virtual void event(typename gesture_traits::on_drag_type g, offset_type offset) {}
  virtual void event(typename gesture_traits::on_up_type g, offset_type offset) {
    if (!ignore_events && is_downed()) {
      set_down(false);
    }
  }
  virtual bool event(typename gesture_traits::on_over_type g, offset_type offset) {
    if (!ignore_events && usagi::geometry::contain(frame(), g.position)) {
      set_over(true);
      return true;
    }
    return false;
  }
  virtual void event(typename gesture_traits::on_out_type g, offset_type offset) {
    if (is_overed()) {
      set_over(false);
    }
  }
  virtual bool event(typename gesture_traits::on_double_type g, offset_type offset) {
    return false;
  }
  virtual bool event(typename gesture_traits::on_wheel_type g, offset_type offset) { return false; }

  virtual void set_down(bool flag) { parameter_downed = flag; }
  virtual void set_over(bool flag) { parameter_overed = flag; }

  [[nodiscard]] virtual bool is_downed() const { return parameter_downed; }
  [[nodiscard]] virtual bool is_overed() const { return parameter_overed; }

  virtual constexpr size_type bounds() const { return content.size(); }
  virtual constexpr rect_type frame() const { return content; }

  virtual constexpr void set_enabled(bool flag) { enabled = flag; }
  [[nodiscard]] virtual constexpr bool is_enabled() const { return enabled; }

  void set_ignore_events(bool flag) { ignore_events = flag; }
  [[nodiscard]] bool is_ignoring_events() const { return ignore_events; }

private:
  rect_type content{};
  bool ignore_events{false};
  bool enabled{true};
  bool parameter_downed{false};
  bool parameter_overed{false};
};
} // namespace usagi::ui
