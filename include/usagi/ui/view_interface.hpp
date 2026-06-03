#pragma once

#include <usagi/concepts/floating_point.hpp>
#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/type/gesture.hpp>

namespace usagi::ui {
/// Abstract interface for drawable, gestural UI views.
///
/// @tparam ValueType Floating-point geometry value type.
/// @tparam DrawContextType Mutable drawing context type.
/// @tparam GestureParameterType Raw gesture parameter payload type.
template <usagi::concepts::floating_point ValueType, class DrawContextType,
          class GestureParameterType>
class view_interface {
public:
  /// Shared geometry value type.
  using value_type = ValueType;
  /// Point type using `value_type`.
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  /// Rectangle type using `value_type`.
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  /// Size type using `value_type`.
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  /// Transform type using `value_type`.
  using transform_type = typename usagi::geometry::geometry_traits<value_type>::transform_type;
  /// Mutable drawing context type.
  using draw_context_type = DrawContextType;
  /// Draw and event offset type.
  using offset_type = point_type;
  /// Raw gesture parameter payload type.
  using gesture_parameter_type = GestureParameterType;
  /// Gesture event type bundle for `gesture_parameter_type`.
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  /// Destroys the interface through a base pointer.
  virtual constexpr ~view_interface() = default;

  /// Draws the view.
  ///
  /// @param context Mutable drawing context.
  /// @param offset Accumulated offset from the root view.
  virtual constexpr void draw(draw_context_type &context, offset_type offset) = 0;

  /// Returns the view-local bounds size.
  ///
  /// @return Size of this view in local coordinates.
  [[nodiscard]] virtual constexpr size_type bounds() const = 0;
  /// Returns the frame in parent coordinates.
  ///
  /// @return Rectangle locating this view in its parent coordinate system.
  [[nodiscard]] virtual constexpr rect_type frame() const = 0;

  /// Handles a pointer or button press event.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the event is consumed; otherwise `false`.
  virtual constexpr bool event(typename gesture_traits::on_down_type g, offset_type offset) = 0;
  /// Handles a drag event.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  virtual constexpr void event(typename gesture_traits::on_drag_type g, offset_type offset) = 0;
  /// Handles a pointer or button release event.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  virtual constexpr void event(typename gesture_traits::on_up_type g, offset_type offset) = 0;
  /// Handles a pointer over event.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the event is consumed; otherwise `false`.
  virtual constexpr bool event(typename gesture_traits::on_over_type g, offset_type offset) = 0;
  /// Handles a pointer out event.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  virtual constexpr void event(typename gesture_traits::on_out_type g, offset_type offset) = 0;
  /// Handles a double-click event.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the event is consumed; otherwise `false`.
  virtual constexpr bool event(typename gesture_traits::on_double_type g, offset_type offset) = 0;
  /// Handles a wheel event.
  ///
  /// @param g Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the event is consumed; otherwise `false`.
  virtual constexpr bool event(typename gesture_traits::on_wheel_type g, offset_type offset) = 0;

  /// Updates the active press state.
  ///
  /// @param flag New press-state value.
  virtual constexpr void set_down(bool flag) = 0;
  /// Updates the pointer-over state.
  ///
  /// @param flag New over-state value.
  virtual constexpr void set_over(bool flag) = 0;
  /// Returns whether the view is currently pressed.
  ///
  /// @return Current press-state value.
  [[nodiscard]] virtual constexpr bool is_downed() const = 0;
  /// Returns whether the pointer is currently over the view.
  ///
  /// @return Current over-state value.
  [[nodiscard]] virtual constexpr bool is_overed() const = 0;

  /// Updates whether the view participates in draw and event traversal.
  ///
  /// @param flag New enabled-state value.
  virtual constexpr void set_enabled(bool flag) = 0;
  /// Returns whether the view is enabled.
  ///
  /// @return Current enabled-state value.
  [[nodiscard]] virtual constexpr bool is_enabled() const = 0;

  /// Returns the layout-after transform.
  ///
  /// @return Transform applied after frame placement.
  [[nodiscard]] virtual constexpr transform_type transform() const = 0;
  /// Replaces the layout-after transform.
  ///
  /// @param t New transform value.
  virtual constexpr void set_transform(transform_type t) = 0;

  /// Returns the transform translation.
  ///
  /// @return Translation applied after frame placement.
  [[nodiscard]] virtual constexpr point_type translation() const = 0;
  /// Updates the transform translation.
  ///
  /// @param p New translation value.
  virtual constexpr void set_translation(point_type p) = 0;

  /// Returns the transform rotation.
  ///
  /// @return Current rotation angle in radians.
  [[nodiscard]] virtual constexpr value_type rotation() const = 0;
  /// Updates the transform rotation without changing the current origin.
  ///
  /// @param r New rotation angle in radians.
  virtual constexpr void set_rotation(value_type r) = 0;

  /// Returns the transform scale.
  ///
  /// @return Current x and y scale factors.
  [[nodiscard]] virtual constexpr point_type scale() const = 0;
  /// Updates the transform scale without changing the current origin.
  ///
  /// @param s New x and y scale factors.
  virtual constexpr void set_scale(point_type s) = 0;
  /// Updates the transform scale and transform origin together.
  ///
  /// @param s New x and y scale factors.
  /// @param origin Origin used by the scale operation.
  virtual constexpr void set_scale(point_type s, point_type origin) = 0;
};
} // namespace usagi::ui
