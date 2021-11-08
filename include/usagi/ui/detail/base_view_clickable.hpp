#pragma once

#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/geometry/rect/function.hpp>
#include <usagi/type/mouse.hpp>

namespace usagi::ui::detail {
template <usagi::utility::arithmetic ValueType, class MouseParameterType>
class base_view_clickable {
public:
  using value_type = ValueType;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using mouse_parameter_type = MouseParameterType;
  using mouse_traits = typename usagi::type::mouse_traits<mouse_parameter_type>;

  void set_mouse_down(bool flag) { mouse_downed = flag; }
  void set_mouse_over(bool flag) { mouse_overed = flag; }

  [[nodiscard]] bool is_mouse_downed() const { return mouse_downed; }
  [[nodiscard]] bool is_mouse_overed() const { return mouse_overed; }

  template <class ChildrenType>
  void on_event(typename mouse_traits::on_down_type mouse, ChildrenType& children) {
    set_mouse_down(true);
    auto point = point_type{mouse.x, mouse.y};
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        child.set_mouse_down(true);
        child.event(mouse);
      }
    }
  }

  template <class ChildrenType>
  void on_event(typename mouse_traits::on_drag_type mouse, ChildrenType& children) {
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_mouse_downed()) {
        child.event(mouse);
      }
    }
  }

  template <class ChildrenType>
  void on_event(typename mouse_traits::on_up_type mouse, ChildrenType& children) {
    set_mouse_down(false);
    auto point = point_type{mouse.x, mouse.y};
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_mouse_downed()) {
        child.set_mouse_down(false);
        child.event(mouse);
      }
    }
  }

  // ここに来るイベントは contain を想定する
  template <class ChildrenType>
  void on_event(typename mouse_traits::on_over_type mouse, ChildrenType& children) {
    set_mouse_over(true);
    auto point = point_type{mouse.x, mouse.y};
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        child.set_mouse_over(true);
        child.event(mouse);
      } else if (child.is_mouse_overed() == true) {
        child.set_mouse_over(false);
        child.event(typename mouse_traits::on_out_type{mouse});
      }
    }
  }

  template <class ChildrenType>
  void on_event(typename mouse_traits::on_out_type mouse, ChildrenType& children) {
    set_mouse_over(false);
    for (auto &value : children) {
      auto &child = value.second;
      child.event(mouse);
    }
  }

  template <class ChildrenType>
  void on_event(typename mouse_traits::on_double_click_type mouse, ChildrenType& children) {
    auto point = point_type{mouse.x, mouse.y};
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point))
        child.event(mouse);
    }
  }

  template <class ChildrenType>
  void on_event(typename mouse_traits::on_wheel_type mouse, ChildrenType& children) {
    auto point = point_type{mouse.x, mouse.y};
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point))
        child.event(mouse);
    }
  }

private:
  bool mouse_downed{false};
  bool mouse_overed{false};
};
}