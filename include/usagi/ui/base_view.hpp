#pragma once

#include <usagi/concepts/geometry.hpp>
#include <usagi/geometry/rect/function.hpp>
#include <usagi/ui/view_interface.hpp>

namespace usagi::ui {
/// Basic view implementation with frame, enabled state, and simple hit tracking.
///
/// @tparam ValueType Arithmetic geometry value type.
/// @tparam DrawContextType Mutable drawing context type.
/// @tparam GestureParameterType Raw gesture parameter payload type.
template <usagi::concepts::arithmetic ValueType, class DrawContextType, class GestureParameterType>
class base_view : public view_interface<ValueType, DrawContextType, GestureParameterType> {
  using view_interface_type = view_interface<ValueType, DrawContextType, GestureParameterType>;

public:
  /// Shared geometry value type.
  using value_type = typename view_interface_type::value_type;
  /// Point type using `value_type`.
  using point_type = typename view_interface_type::point_type;
  /// Rectangle type using `value_type`.
  using rect_type = typename view_interface_type::rect_type;
  /// Size type using `value_type`.
  using size_type = typename view_interface_type::size_type;
  /// Transform type using `value_type`.
  using transform_type = typename usagi::geometry::geometry_traits<value_type>::transform_type;
  /// Mutable drawing context type.
  using draw_context_type = typename view_interface_type::draw_context_type;
  /// Draw and event offset type.
  using offset_type = typename view_interface_type::offset_type;
  /// Raw gesture parameter payload type.
  using gesture_parameter_type = typename view_interface_type::gesture_parameter_type;
  /// Gesture event type bundle.
  using gesture_traits = typename view_interface_type::gesture_traits;

  /// Creates a base view with a default frame.
  base_view() = default;

  /// Creates a base view with the given frame.
  ///
  /// @param frame Rectangle-like frame in parent coordinates.
  constexpr explicit base_view(const usagi::concepts::geometry::rect_concept auto &frame)
      : content{frame} {}

  /// Destroys the base view.
  constexpr ~base_view() override = default;

  /// Draws nothing.
  ///
  /// @param context Mutable drawing context.
  /// @param offset Accumulated offset from the root view.
  constexpr void draw(draw_context_type &context, offset_type offset) override {}

  /// Handles a down event by hit-testing against local bounds.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the event is inside bounds and events are not ignored.
  constexpr bool event(typename gesture_traits::on_down_type g, offset_type offset) override {
    if (!ignore_events && usagi::geometry::contain(rect_type{bounds()}, g.position)) {
      set_down(true);
      return true;
    }
    return false;
  }

  /// Ignores drag events.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  constexpr void event(typename gesture_traits::on_drag_type g, offset_type offset) override {}

  /// Clears the down state when this view is tracking a press.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  constexpr void event(typename gesture_traits::on_up_type g, offset_type offset) override {
    if (!ignore_events && is_downed()) {
      set_down(false);
    }
  }

  /// Handles an over event by hit-testing against local bounds.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the event is inside bounds and events are not ignored.
  constexpr bool event(typename gesture_traits::on_over_type g, offset_type offset) override {
    if (!ignore_events && usagi::geometry::contain(rect_type{bounds()}, g.position)) {
      set_over(true);
      return true;
    }
    return false;
  }

  /// Clears the over state when this view is tracking hover.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  constexpr void event(typename gesture_traits::on_out_type g, offset_type offset) override {
    if (is_overed()) {
      set_over(false);
    }
  }

  /// Ignores double-click events.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return Always `false`.
  constexpr bool event(typename gesture_traits::on_double_type g, offset_type offset) override {
    return false;
  }

  /// Ignores wheel events.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return Always `false`.
  constexpr bool event(typename gesture_traits::on_wheel_type g, offset_type offset) override {
    return false;
  }

  /// Updates the active press state.
  ///
  /// @param flag New press-state value.
  constexpr void set_down(bool flag) override { parameter_downed = flag; }
  /// Updates the pointer-over state.
  ///
  /// @param flag New over-state value.
  constexpr void set_over(bool flag) override { parameter_overed = flag; }

  /// Returns whether the view is currently pressed.
  ///
  /// @return Current press-state value.
  [[nodiscard]] constexpr bool is_downed() const override { return parameter_downed; }
  /// Returns whether the pointer is currently over the view.
  ///
  /// @return Current over-state value.
  [[nodiscard]] constexpr bool is_overed() const override { return parameter_overed; }

  /// Returns the view-local bounds size.
  ///
  /// @return Size derived from the stored frame.
  [[nodiscard]] constexpr size_type bounds() const override { return content.size(); }
  /// Returns the frame in parent coordinates.
  ///
  /// @return Stored frame rectangle.
  [[nodiscard]] constexpr rect_type frame() const override { return content; }

  /// Updates whether the view participates in draw and event traversal.
  ///
  /// @param flag New enabled-state value.
  constexpr void set_enabled(bool flag) override { enabled = flag; }
  /// Returns whether the view is enabled.
  ///
  /// @return Current enabled-state value.
  [[nodiscard]] constexpr bool is_enabled() const override { return enabled; }

  /// Updates whether this base view ignores its own hit-test events.
  ///
  /// @param flag New ignore-events value.
  void set_ignore_events(bool flag) { ignore_events = flag; }
  /// Returns whether this base view ignores its own hit-test events.
  ///
  /// @return Current ignore-events value.
  [[nodiscard]] bool is_ignoring_events() const { return ignore_events; }

  /// Returns the layout-after transform.
  ///
  /// @return Stored transform value.
  [[nodiscard]] constexpr transform_type transform() const { return content_transform; }
  /// Replaces the layout-after transform.
  ///
  /// @param t New transform value.
  constexpr void set_transform(transform_type t) { content_transform = t; }

  /// Returns the transform translation.
  ///
  /// @return Translation applied after frame placement.
  [[nodiscard]] constexpr point_type translation() const {
    return content_transform.translation();
  }
  /// Updates the transform translation.
  ///
  /// @param p New translation value.
  constexpr void set_translation(point_type p) {
    content_transform =
        transform_type{p, content_transform.rotation(), content_transform.scale(),
                       content_transform.origin()};
  }

  /// Returns the transform scale.
  ///
  /// @return Current x and y scale factors.
  [[nodiscard]] constexpr point_type scale() const { return content_transform.scale(); }
  /// Updates the transform scale without changing the current origin.
  ///
  /// @param s New x and y scale factors.
  constexpr void set_scale(point_type s) {
    content_transform =
        transform_type{content_transform.translation(), content_transform.rotation(), s,
                       content_transform.origin()};
  }
  /// Updates the transform scale and transform origin together.
  ///
  /// @param s New x and y scale factors.
  /// @param origin Origin used by the scale operation.
  constexpr void set_scale(point_type s, point_type origin) {
    content_transform =
        transform_type{content_transform.translation(), content_transform.rotation(), s, origin};
  }

private:
  rect_type content{};
  transform_type content_transform{};
  bool ignore_events{false};
  bool enabled{true};
  bool parameter_downed{false};
  bool parameter_overed{false};
};
} // namespace usagi::ui
