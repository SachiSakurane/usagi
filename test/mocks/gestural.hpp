#pragma once

#include <usagi/type/gesture.hpp>

template <class ValueType>
struct Gestural {
  using gesture_parameter_type = usagi::type::gesture_default_parameter<ValueType>;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;
  bool event(typename gesture_traits::on_down_type);
  bool event(typename gesture_traits::on_drag_type);
  void event(typename gesture_traits::on_up_type);
  bool event(typename gesture_traits::on_over_type);
  void event(typename gesture_traits::on_out_type);
  bool event(typename gesture_traits::on_double_type);
  bool event(typename gesture_traits::on_wheel_type);
  void set_mouse_down(bool flag);
  void set_mouse_over(bool flag);
  bool is_mouse_downed();
  bool is_mouse_overed();
};

template <class ValueType>
struct UnGestural {
  using gesture_parameter_type = usagi::type::gesture_default_parameter<ValueType>;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;
  bool event(typename gesture_traits::on_down_type);
  bool event(typename gesture_traits::on_drag_type);
  void event(typename gesture_traits::on_up_type);
  bool event(typename gesture_traits::on_over_type);
  // void event(typename gesture_traits::on_out_type);
  bool event(typename gesture_traits::on_wheel_type);
};
