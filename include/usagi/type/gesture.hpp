#pragma once

#include <usagi/concepts/arithmetic.hpp>

namespace usagi::type {
template <usagi::concepts::arithmetic ValueType>
struct gesture_default_parameter {
  ValueType x, y, d;
};

struct gesture {
  struct on_down {};
  struct on_drag {};
  struct on_up {};
  struct on_over {};
  struct on_out {};
  struct on_double {};
  struct on_wheel {};
};

template <class ParameterType>
struct legacy_gesture {
  struct on_down : ParameterType {};
  struct on_drag : ParameterType {};
  struct on_up : ParameterType {};
  struct on_over : ParameterType {};
  struct on_out : ParameterType {};
  struct on_double : ParameterType {};
  struct on_wheel : ParameterType {};
};

template <class ParameterType>
struct gesture_traits {
  using parameter_type = ParameterType;
  using on_down_type = typename legacy_gesture<parameter_type>::on_down;
  using on_drag_type = typename legacy_gesture<parameter_type>::on_drag;
  using on_up_type = typename legacy_gesture<parameter_type>::on_up;
  using on_over_type = typename legacy_gesture<parameter_type>::on_over;
  using on_out_type = typename legacy_gesture<parameter_type>::on_out;
  using on_double_type = typename legacy_gesture<parameter_type>::on_double;
  using on_wheel_type = typename legacy_gesture<parameter_type>::on_wheel;
};
} // namespace usagi::type
