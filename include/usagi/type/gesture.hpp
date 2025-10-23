#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/geometry/point.hpp>

namespace usagi::type {
template <usagi::concepts::arithmetic ValueType>
struct gesture_parameter {
  using value_type = ValueType;
  usagi::geometry::point<ValueType> position;
  ValueType wheel_delta;
  bool l, r, shift, ctrl, alt;
};

template <class ParameterType>
struct gesture {
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
  using offset_type = usagi::geometry::point<typename parameter_type::value_type>;
  using on_down_type = typename gesture<parameter_type>::on_down;
  using on_drag_type = typename gesture<parameter_type>::on_drag;
  using on_up_type = typename gesture<parameter_type>::on_up;
  using on_over_type = typename gesture<parameter_type>::on_over;
  using on_out_type = typename gesture<parameter_type>::on_out;
  using on_double_type = typename gesture<parameter_type>::on_double;
  using on_wheel_type = typename gesture<parameter_type>::on_wheel;
};
} // namespace usagi::type
