#pragma once

#include <usagi/type/gesture.hpp>

template <class ValueType>
struct Gestural {
  using gesture_parameter_type = usagi::type::gesture_parameter<ValueType>;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;
  using offset_type = typename usagi::type::gesture_traits<gesture_parameter_type>::offset_type;
  bool event(typename gesture_traits::on_down_type, offset_type);
  bool event(typename gesture_traits::on_drag_type, offset_type);
  void event(typename gesture_traits::on_up_type, offset_type);
  bool event(typename gesture_traits::on_over_type, offset_type);
  void event(typename gesture_traits::on_out_type, offset_type);
  bool event(typename gesture_traits::on_double_type, offset_type);
  bool event(typename gesture_traits::on_wheel_type, offset_type);
  void set_down(bool flag);
  void set_over(bool flag);
  bool is_downed();
  bool is_overed();
};

template <class ValueType>
struct UnGestural {
  using gesture_parameter_type = usagi::type::gesture_parameter<ValueType>;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;
  using offset_type = typename usagi::type::gesture_traits<gesture_parameter_type>::offset_type;
  bool event(typename gesture_traits::on_down_type, offset_type);
  bool event(typename gesture_traits::on_drag_type, offset_type);
  void event(typename gesture_traits::on_up_type, offset_type);
  bool event(typename gesture_traits::on_over_type, offset_type);
  // void event(typename gesture_traits::on_out_type, offset_type);
  bool event(typename gesture_traits::on_double_type, offset_type);
  bool event(typename gesture_traits::on_wheel_type, offset_type);
};
