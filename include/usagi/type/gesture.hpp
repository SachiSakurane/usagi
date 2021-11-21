#pragma once

#include <type_traits>

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/type/gestural_parameter.hpp>

namespace usagi::type {
template <usagi::concepts::arithmetic ValueType>
struct gesture_default_parameter {
  ValueType x, y, d;
};

template <usagi::concepts::type::gestural_parameter ParameterType>
struct gesture {
  struct on_down : ParameterType {};
  struct on_drag : ParameterType {};
  struct on_up : ParameterType {};
  struct on_over : ParameterType {};
  struct on_out : ParameterType {};
  struct on_double : ParameterType {};
  struct on_wheel : ParameterType {};
};

template <usagi::concepts::type::gestural_parameter ParameterType>
struct gesture_traits {
  using parameter_type = ParameterType;
  using on_down_type = typename gesture<parameter_type>::on_down;
  using on_drag_type = typename gesture<parameter_type>::on_drag;
  using on_up_type = typename gesture<parameter_type>::on_up;
  using on_over_type = typename gesture<parameter_type>::on_over;
  using on_out_type = typename gesture<parameter_type>::on_out;
  using on_double_type = typename gesture<parameter_type>::on_double;
  using on_wheel_type = typename gesture<parameter_type>::on_wheel;
};
} // namespace usagi::type
