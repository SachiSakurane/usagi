#pragma once

#include <cassert>
#include <algorithm>
#include <cstddef>
#include <unordered_map>
#include <utility>
#include <vector>

#include <usagi/concepts/floating_point.hpp>
#include <usagi/concepts/geometry.hpp>
#include <usagi/geometry.hpp>
#include <usagi/geometry/transform/function.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/draw_clip.hpp>
#include <usagi/ui/draw_transform.hpp>
#include <usagi/ui/view.hpp>

namespace usagi::ui {
/// Composite view that owns child views and dispatches draw/events by z-order.
///
/// Children are drawn from back to front and hit-tested from front to back.
///
/// @tparam ValueType Floating-point geometry value type.
/// @tparam DrawContextType Mutable drawing context type.
/// @tparam GestureParameterType Raw gesture parameter payload type.
template <usagi::concepts::floating_point ValueType, class DrawContextType,
          class GestureParameterType>
struct view_stack : public usagi::ui::base_view<ValueType, DrawContextType, GestureParameterType> {
  /// Base view type.
  using base_view_type = usagi::ui::base_view<ValueType, DrawContextType, GestureParameterType>;

  /// Shared geometry value type.
  using value_type = typename base_view_type::value_type;
  /// Point type using `value_type`.
  using point_type = typename base_view_type::point_type;
  /// Rectangle type using `value_type`.
  using rect_type = typename base_view_type::rect_type;
  /// Size type using `value_type`.
  using size_type = typename base_view_type::size_type;
  /// Mutable drawing context type.
  using draw_context_type = typename base_view_type::draw_context_type;
  /// Draw and event offset type.
  using offset_type = typename base_view_type::offset_type;
  /// Raw gesture parameter payload type.
  using gesture_parameter_type = typename base_view_type::gesture_parameter_type;
  /// Gesture event type bundle.
  using gesture_traits = typename base_view_type::gesture_traits;

  /// Owned child view handle type.
  using child_view_type = usagi::ui::view<value_type, draw_context_type, gesture_parameter_type>;
  /// Stable key type used to identify a child view.
  using child_view_key_type = size_t;

  /// Creates a view stack with a default frame.
  view_stack() = default;

  /// Creates a view stack with the given frame.
  ///
  /// @param frame Rectangle-like frame in parent coordinates.
  constexpr explicit view_stack(const usagi::concepts::geometry::rect_concept auto &frame)
      : base_view_type{frame} {}

  /// Draws enabled children from back to front.
  ///
  /// @param context Mutable drawing context.
  /// @param offset Accumulated offset from the root view.
  void draw(draw_context_type &context, offset_type offset) override {
    const auto draw_children = [&] {
      draw_children_unclipped(context, offset);
    };

    if (draw_clipping) {
      usagi::ui::draw_with_clip(context, draw_clip_rect(offset), draw_children);
      return;
    }

    draw_children();
  }

  /// Dispatches a down event to the frontmost enabled child under the position.
  ///
  /// @param parameter Gesture parameter in stack-local coordinates.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when a child consumes the event; otherwise `false`.
  bool event(typename gesture_traits::on_down_type parameter, offset_type offset) override {
    if (is_event_position_clipped(parameter)) {
      return false;
    }

    this->set_down(true);
    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (child.is_enabled() && contains_child_position(child, parameter.position)) {
        if (child.event(local_parameter(parameter, child), offset + child_origin(child))) {
          child.set_down(true);
          return true;
        }
      }
    }
    return false;
  }

  /// Dispatches a drag event to children currently tracking a down state.
  ///
  /// @param parameter Gesture parameter in stack-local coordinates.
  /// @param offset Accumulated offset from the root view.
  void event(typename gesture_traits::on_drag_type parameter, offset_type offset) override {
    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (child.is_downed()) {
        child.event(local_parameter(parameter, child), offset + child_origin(child));
      }
    }
  }

  /// Dispatches an up event to children currently tracking a down state.
  ///
  /// @param parameter Gesture parameter in stack-local coordinates.
  /// @param offset Accumulated offset from the root view.
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
  /// Dispatches an over event to the frontmost enabled child under the position.
  ///
  /// Children that were previously overed but are no longer selected receive an
  /// out event.
  ///
  /// @param parameter Gesture parameter in stack-local coordinates.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when a child consumes the over event; otherwise `false`.
  bool event(typename gesture_traits::on_over_type parameter, offset_type offset) override {
    this->set_over(true);
    auto is_resolved = false;
    const auto can_hit_new_child = !is_event_position_clipped(parameter);
    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (can_hit_new_child && !is_resolved && child.is_enabled() &&
          contains_child_position(child, parameter.position)) {
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

  /// Dispatches an out event to children currently tracking an over state.
  ///
  /// @param parameter Gesture parameter in stack-local coordinates.
  /// @param offset Accumulated offset from the root view.
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

  /// Dispatches a double-click event to the frontmost enabled child under the position.
  ///
  /// @param parameter Gesture parameter in stack-local coordinates.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when a child consumes the event; otherwise `false`.
  bool event(typename gesture_traits::on_double_type parameter, offset_type offset) override {
    if (is_event_position_clipped(parameter)) {
      return false;
    }

    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (child.is_enabled() && contains_child_position(child, parameter.position)) {
        if (child.event(local_parameter(parameter, child), offset + child_origin(child))) {
          return true;
        }
      }
    }
    return false;
  }

  /// Dispatches a wheel event to the frontmost enabled child under the position.
  ///
  /// @param parameter Gesture parameter in stack-local coordinates.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when a child consumes the event; otherwise `false`.
  bool event(typename gesture_traits::on_wheel_type parameter, offset_type offset) override {
    if (is_event_position_clipped(parameter)) {
      return false;
    }

    for (auto it = child_order.rbegin(); it != child_order.rend(); ++it) {
      auto &child = child_views.at(*it);
      if (child.is_enabled() && contains_child_position(child, parameter.position)) {
        if (child.event(local_parameter(parameter, child), offset + child_origin(child))) {
          return true;
        }
      }
    }
    return false;
  }

  /// Adds a child view at the front of the z-order.
  ///
  /// @param child_view Child view handle to store.
  /// @return Stable key assigned to the child.
  child_view_key_type add_child_view(child_view_type &&child_view) {
    const auto current_index = children_next_index;
    children_next_index += 1;
    child_views.try_emplace(current_index, std::forward<child_view_type>(child_view));
    child_order.emplace_back(current_index);
    return current_index;
  }

  /// Returns a child view by key.
  ///
  /// @param index Child key returned by `add_child_view`.
  /// @return Mutable reference to the child view.
  /// @pre `index` must identify an existing child.
  child_view_type &get_child_view(child_view_key_type index) {
    assert(child_views.find(index) != child_views.end());
    return child_views.at(index);
  }

  /// Removes a child view by key without dispatching synthetic gesture cleanup.
  ///
  /// @param index Child key returned by `add_child_view`.
  /// @return `true` when a child was removed; otherwise `false`.
  bool remove_child_view(child_view_key_type index) {
    if (auto it = child_views.find(index); it != child_views.end()) {
      child_views.erase(it);
      remove_child_order(index);
      return true;
    }
    return false;
  }

  /// Returns the number of owned child views.
  ///
  /// @return Current child view count.
  [[nodiscard]] size_t child_view_size() const { return child_views.size(); }

  /// Updates whether new hit-test events are clipped to stack bounds.
  ///
  /// @param flag New event-clipping value.
  void set_event_clipping(bool flag) { event_clipping = flag; }
  /// Returns whether new hit-test events are clipped to stack bounds.
  ///
  /// @return Current event-clipping value.
  [[nodiscard]] bool is_event_clipping() const { return event_clipping; }

  /// Updates whether child drawing is clipped to stack bounds.
  ///
  /// Draw clipping is opt-in. When enabled, the stack clips all children to its
  /// own placed bounds before applying each child transform.
  ///
  /// @param flag New draw-clipping value.
  void set_draw_clipping(bool flag) { draw_clipping = flag; }
  /// Returns whether child drawing is clipped to stack bounds.
  ///
  /// @return Current draw-clipping value.
  [[nodiscard]] bool is_draw_clipping() const { return draw_clipping; }

  /// Moves a child to the front of the z-order.
  ///
  /// @param index Child key returned by `add_child_view`.
  /// @return `true` when the child exists and was moved; otherwise `false`.
  bool bring_child_to_front(child_view_key_type index) {
    if (child_views.find(index) == child_views.end()) {
      return false;
    }
    remove_child_order(index);
    child_order.emplace_back(index);
    return true;
  }

  /// Moves a child to the back of the z-order.
  ///
  /// @param index Child key returned by `add_child_view`.
  /// @return `true` when the child exists and was moved; otherwise `false`.
  bool send_child_to_back(child_view_key_type index) {
    if (child_views.find(index) == child_views.end()) {
      return false;
    }
    remove_child_order(index);
    child_order.insert(child_order.begin(), index);
    return true;
  }

private:
  /// Returns whether a new hit-test event is clipped by stack bounds.
  template <class ParameterType>
  bool is_event_position_clipped(const ParameterType &parameter) const {
    return event_clipping && !usagi::geometry::contain(rect_type{this->bounds()}, parameter.position);
  }

  /// Returns this stack's draw clipping rectangle in root coordinates.
  rect_type draw_clip_rect(offset_type offset) const {
    return rect_type{offset, this->bounds()};
  }

  /// Draws enabled children without applying stack-level clipping.
  ///
  /// @param context Mutable drawing context.
  /// @param offset Accumulated offset from the root view.
  void draw_children_unclipped(draw_context_type &context, offset_type offset) {
    for (auto key : child_order) {
      auto &child = child_views.at(key);
      if (child.is_enabled()) {
        const auto child_offset = offset + child_origin(child);
        usagi::ui::draw_with_transform(context, child.transform(), child_offset,
                                       [&] { child.draw(context, child_offset); });
      }
    }
  }

  /// Returns a child origin in stack-local coordinates.
  static offset_type child_origin(const child_view_type &child) {
    return offset_type{child.frame().l(), child.frame().t()} + child.translation();
  }

  static bool contains_child_position(const child_view_type &child, point_type position) {
    return usagi::geometry::contain(rect_type{child.bounds()},
                                    child_local_position(child, position));
  }

  /// Converts a stack-local gesture parameter to child-local coordinates.
  template <class ParameterType>
  static ParameterType local_parameter(ParameterType parameter, const child_view_type &child) {
    parameter.position = child_local_position(child, parameter.position);
    return parameter;
  }

  static point_type child_local_position(const child_view_type &child, point_type position) {
    const auto frame_origin = offset_type{child.frame().l(), child.frame().t()};
    return usagi::geometry::inverse_transform_point(child.transform(), position - frame_origin);
  }

  /// Converts any gesture parameter payload to an out-event payload.
  template <class ParameterType>
  static typename gesture_traits::on_out_type out_parameter(const ParameterType &parameter) {
    return typename gesture_traits::on_out_type{static_cast<const gesture_parameter_type &>(
        parameter)};
  }

  /// Removes a child key from the z-order list.
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
  bool draw_clipping{false};
};

} // namespace usagi::ui
