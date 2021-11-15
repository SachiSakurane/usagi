#pragma once

#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/geometry/rect/function.hpp>
#include <usagi/type/gesture.hpp>

namespace usagi::ui::detail {
template <usagi::concepts::arithmetic ValueType, class MouseParameterType>
class base_view_gesture {
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
  bool on_event(typename mouse_traits::on_down_type mouse, ChildrenType &children) {
    set_mouse_down(true);
    auto point = point_type{mouse.x, mouse.y};
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        child.set_mouse_down(true);
        if (child.event(mouse)) {
          return true;
        }
      }
    }
    return false;
  }

  template <class ChildrenType>
  void on_event(typename mouse_traits::on_drag_type mouse, ChildrenType &children) {
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (child.is_mouse_downed()) {
        child.event(mouse);
      }
    }
  }

  template <class ChildrenType>
  void on_event(typename mouse_traits::on_up_type mouse, ChildrenType &children) {
    set_mouse_down(false);
    auto point = point_type{mouse.x, mouse.y};
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (child.is_mouse_downed()) {
        child.set_mouse_down(false);
        child.event(mouse);
      }
    }
  }

  // ここに来るイベントは contain を想定する
  template <class ChildrenType>
  bool on_event(typename mouse_traits::on_over_type mouse, ChildrenType &children) {
    set_mouse_over(true);
    auto point = point_type{mouse.x, mouse.y};
    auto is_resolved = false;
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (!is_resolved && child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        child.set_mouse_over(true);
        is_resolved = child.event(mouse);
      } else if (child.is_mouse_overed() == true) {
        child.set_mouse_over(false);
        child.event(typename mouse_traits::on_out_type{mouse});
      }
    }
    return is_resolved;
  }

  template <class ChildrenType>
  void on_event(typename mouse_traits::on_out_type mouse, ChildrenType &children) {
    set_mouse_over(false);
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      child.event(mouse);
    }
  }

  template <class ChildrenType>
  bool on_event(typename mouse_traits::on_double_type mouse, ChildrenType &children) {
    auto point = point_type{mouse.x, mouse.y};
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        if (child.event(mouse)) {
          return true;
        }
      }
    }
    return false;
  }

  template <class ChildrenType>
  bool on_event(typename mouse_traits::on_wheel_type mouse, ChildrenType &children) {
    auto point = point_type{mouse.x, mouse.y};
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        if (child.event(mouse)) {
          return true;
        }
      }
    }
    return false;
  }

private:
  bool mouse_downed{false};
  bool mouse_overed{false};
};
} // namespace usagi::ui::detail