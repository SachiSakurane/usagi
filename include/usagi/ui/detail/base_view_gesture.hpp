#pragma once

#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/geometry/rect/function.hpp>
#include <usagi/type/gesture.hpp>

namespace usagi::ui::detail {
template <usagi::concepts::arithmetic ValueType, class GestureParameterType>
class base_view_gesture {
public:
  using value_type = ValueType;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using gesture_parameter_type = GestureParameterType;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  void set_down(bool flag) { parameter_downed = flag; }
  void set_over(bool flag) { parameter_overed = flag; }

  [[nodiscard]] bool on_downed() const { return parameter_downed; }
  [[nodiscard]] bool on_overed() const { return parameter_overed; }

  template <class ChildrenType>
  bool on_event(typename gesture_traits::on_down_type parameter, ChildrenType &children) {
    set_down(true);
    auto point = point_type{parameter.x, parameter.y};
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        child.set_down(true);
        if (child.event(parameter)) {
          return true;
        }
      }
    }
    return false;
  }

  template <class ChildrenType>
  void on_event(typename gesture_traits::on_drag_type parameter, ChildrenType &children) {
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (child.on_downed()) {
        child.event(parameter);
      }
    }
  }

  template <class ChildrenType>
  void on_event(typename gesture_traits::on_up_type parameter, ChildrenType &children) {
    set_down(false);
    auto point = point_type{parameter.x, parameter.y};
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (child.on_downed()) {
        child.set_down(false);
        child.event(parameter);
      }
    }
  }

  // ここに来るイベントは contain を想定する
  template <class ChildrenType>
  bool on_event(typename gesture_traits::on_over_type parameter, ChildrenType &children) {
    set_over(true);
    auto point = point_type{parameter.x, parameter.y};
    auto is_resolved = false;
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (!is_resolved && child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        child.set_over(true);
        is_resolved = child.event(parameter);
      } else if (child.on_overed() == true) {
        child.set_over(false);
        child.event(typename gesture_traits::on_out_type{parameter});
      }
    }
    return is_resolved;
  }

  template <class ChildrenType>
  void on_event(typename gesture_traits::on_out_type parameter, ChildrenType &children) {
    set_over(false);
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      child.event(parameter);
    }
  }

  template <class ChildrenType>
  bool on_event(typename gesture_traits::on_double_type parameter, ChildrenType &children) {
    auto point = point_type{parameter.x, parameter.y};
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        if (child.event(parameter)) {
          return true;
        }
      }
    }
    return false;
  }

  template <class ChildrenType>
  bool on_event(typename gesture_traits::on_wheel_type parameter, ChildrenType &children) {
    auto point = point_type{parameter.x, parameter.y};
    for (auto it = std::rbegin(children); it != std::rend(children); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        if (child.event(parameter)) {
          return true;
        }
      }
    }
    return false;
  }

private:
  bool parameter_downed{false};
  bool parameter_overed{false};
};
} // namespace usagi::ui::detail