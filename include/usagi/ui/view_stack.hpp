#pragma once

#include <cassert>
#include <algorithm>
#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry.hpp>
#include <usagi/geometry.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/view.hpp>

namespace usagi::ui {
template <usagi::concepts::arithmetic ValueType, class DrawContextType, class GestureParameterType>
struct view_stack : public usagi::ui::base_view<ValueType, DrawContextType, GestureParameterType> {
  using base_view_type = usagi::ui::base_view<ValueType, DrawContextType, GestureParameterType>;

  using value_type = typename base_view_type::value_type;
  using point_type = typename base_view_type::point_type;
  using rect_type = typename base_view_type::rect_type;
  using size_type = typename base_view_type::size_type;
  using draw_context_type = typename base_view_type::draw_context_type;
  using offset_type = typename base_view_type::offset_type;
  using gesture_parameter_type = typename base_view_type::gesture_parameter_type;
  using gesture_traits = typename base_view_type::gesture_traits;

  using child_view_type = usagi::ui::view<value_type, draw_context_type, gesture_parameter_type>;
  using child_view_key_type = size_t;

  view_stack() = default;

  constexpr explicit view_stack(const usagi::concepts::geometry::rect_concept auto &frame)
      : base_view_type{frame} {}

  void draw(draw_context_type &context, offset_type offset) override {
    for (auto key : child_order) {
      auto &child = child_views.at(key);
      if (child.is_enabled()) {
        child.draw(context, offset + child_origin(child));
      }
    }
  }

  bool event(typename gesture_traits::on_down_type parameter, offset_type offset) override {
    if (is_event_position_clipped(parameter)) {
      return false;
    }

    this->set_down(true);
    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), parameter.position)) {
        if (child.event(local_parameter(parameter, child), offset + child_origin(child))) {
          child.set_down(true);
          return true;
        }
      }
    }
    return false;
  }

  void event(typename gesture_traits::on_drag_type parameter, offset_type offset) override {
    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (child.is_downed()) {
        child.event(local_parameter(parameter, child), offset + child_origin(child));
      }
    }
  }

  void event(typename gesture_traits::on_up_type parameter, offset_type offset) override {
    this->set_down(false);
    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (child.is_downed()) {
        child.set_down(false);
        child.event(local_parameter(parameter, child), offset + child_origin(child));
      }
    }
  }

  // ここに来るイベントは contain を想定する
  bool event(typename gesture_traits::on_over_type parameter, offset_type offset) override {
    this->set_over(true);
    auto is_resolved = false;
    const auto can_hit_new_child = !is_event_position_clipped(parameter);
    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (can_hit_new_child && !is_resolved && child.is_enabled() &&
          usagi::geometry::contain(child.frame(), parameter.position)) {
        is_resolved = child.event(local_parameter(parameter, child), offset + child_origin(child));
        if (is_resolved) {
          child.set_over(true);
        }
      } else if (child.is_overed() == true) {
        child.set_over(false);
        child.event(local_parameter(out_parameter(parameter), child), offset + child_origin(child));
      }
    }
    return is_resolved;
  }

  void event(typename gesture_traits::on_out_type parameter, offset_type offset) override {
    this->set_over(false);
    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (child.is_overed()) {
        child.set_over(false);
        child.event(local_parameter(parameter, child), offset + child_origin(child));
      }
    }
  }

  bool event(typename gesture_traits::on_double_type parameter, offset_type offset) override {
    if (is_event_position_clipped(parameter)) {
      return false;
    }

    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), parameter.position)) {
        if (child.event(local_parameter(parameter, child), offset + child_origin(child))) {
          return true;
        }
      }
    }
    return false;
  }

  bool event(typename gesture_traits::on_wheel_type parameter, offset_type offset) override {
    if (is_event_position_clipped(parameter)) {
      return false;
    }

    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), parameter.position)) {
        if (child.event(local_parameter(parameter, child), offset + child_origin(child))) {
          return true;
        }
      }
    }
    return false;
  }

  child_view_key_type add_child_view(child_view_type &&child_view) {
    const auto current_index = children_next_index;
    children_next_index += 1;
    child_views.try_emplace(current_index, std::forward<child_view_type>(child_view));
    child_order.emplace_back(current_index);
    return current_index;
  }

  child_view_type &get_child_view(child_view_key_type index) {
    assert(child_views.find(index) != child_views.end());
    return child_views.at(index);
  }

  bool remove_child_view(child_view_key_type index) {
    if (auto it = child_views.find(index); it != child_views.end()) {
      child_views.erase(it);
      remove_child_order(index);
      return true;
    }
    return false;
  }

  [[nodiscard]] size_t child_view_size() const { return child_views.size(); }

  void set_event_clipping(bool flag) { event_clipping = flag; }
  [[nodiscard]] bool is_event_clipping() const { return event_clipping; }

  bool bring_child_to_front(child_view_key_type index) {
    if (child_views.find(index) == child_views.end()) {
      return false;
    }
    remove_child_order(index);
    child_order.emplace_back(index);
    return true;
  }

  bool send_child_to_back(child_view_key_type index) {
    if (child_views.find(index) == child_views.end()) {
      return false;
    }
    remove_child_order(index);
    child_order.insert(child_order.begin(), index);
    return true;
  }

private:
  template <class ParameterType>
  bool is_event_position_clipped(const ParameterType &parameter) const {
    return event_clipping && !usagi::geometry::contain(rect_type{this->bounds()}, parameter.position);
  }

  static offset_type child_origin(const child_view_type &child) {
    return offset_type{child.frame().l(), child.frame().t()};
  }

  template <class ParameterType>
  static ParameterType local_parameter(ParameterType parameter, const child_view_type &child) {
    parameter.position = parameter.position - child_origin(child);
    return parameter;
  }

  template <class ParameterType>
  static typename gesture_traits::on_out_type out_parameter(const ParameterType &parameter) {
    return typename gesture_traits::on_out_type{static_cast<const gesture_parameter_type &>(
        parameter)};
  }

  void remove_child_order(child_view_key_type index) {
    if (auto it = std::find(child_order.begin(), child_order.end(), index);
        it != child_order.end()) {
      child_order.erase(it);
    }
  }

  size_t children_next_index{0};
  using child_view_map_type = std::unordered_map<child_view_key_type, child_view_type>;
  child_view_map_type child_views;
  std::vector<child_view_key_type> child_order;
  bool event_clipping{true};
};

} // namespace usagi::ui
