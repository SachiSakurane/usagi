#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/geometry/point.hpp>

namespace usagi::type {
/// Raw gesture input state.
///
/// @tparam ValueType Arithmetic coordinate and wheel delta value type.
template <usagi::concepts::arithmetic ValueType>
struct gesture_parameter {
  /// Coordinate and wheel delta value type.
  using value_type = ValueType;
  /// Gesture position.
  usagi::geometry::point<ValueType> position;
  /// Wheel delta for wheel gestures.
  ValueType wheel_delta;
  /// Mouse and modifier button states.
  bool l, r, shift, ctrl, alt;
};

/// Gesture event types derived from a shared parameter payload.
///
/// @tparam ParameterType Base parameter type carried by each event.
template <class ParameterType>
struct gesture {
  /// Pointer or button press event.
  struct on_down : ParameterType {};
  /// Drag event.
  struct on_drag : ParameterType {};
  /// Pointer or button release event.
  struct on_up : ParameterType {};
  /// Pointer over event.
  struct on_over : ParameterType {};
  /// Pointer out event.
  struct on_out : ParameterType {};
  /// Double click event.
  struct on_double : ParameterType {};
  /// Wheel event.
  struct on_wheel : ParameterType {};
};

/// Type aliases for a gesture parameter and its event variants.
///
/// @tparam ParameterType Base parameter type carried by each event.
template <class ParameterType>
struct gesture_traits {
  /// Base gesture parameter type.
  using parameter_type = ParameterType;
  /// Coordinate offset type derived from the parameter value type.
  using offset_type = usagi::geometry::point<typename parameter_type::value_type>;
  /// Pointer or button press event type.
  using on_down_type = typename gesture<parameter_type>::on_down;
  /// Drag event type.
  using on_drag_type = typename gesture<parameter_type>::on_drag;
  /// Pointer or button release event type.
  using on_up_type = typename gesture<parameter_type>::on_up;
  /// Pointer over event type.
  using on_over_type = typename gesture<parameter_type>::on_over;
  /// Pointer out event type.
  using on_out_type = typename gesture<parameter_type>::on_out;
  /// Double click event type.
  using on_double_type = typename gesture<parameter_type>::on_double;
  /// Wheel event type.
  using on_wheel_type = typename gesture<parameter_type>::on_wheel;
};
} // namespace usagi::type
