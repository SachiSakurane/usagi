#pragma once

#include <usagi/type/mouse.hpp>

template <class ValueType>
struct Clickable {
  using mouse_parameter_type = usagi::type::mouse::default_parameter<ValueType>;
  using mouse_traits = typename usagi::type::mouse_traits<mouse_parameter_type>;
  void event(typename mouse_traits::on_down_type);
  void event(typename mouse_traits::on_drag_type);
  void event(typename mouse_traits::on_up_type);
  void event(typename mouse_traits::on_over_type);
  void event(typename mouse_traits::on_out_type);
  void set_mouse_down(bool flag);
  void set_mouse_over(bool flag);
  bool is_mouse_downed();
  bool is_mouse_overed();
};

template <class ValueType>
struct UnClickable {
  using mouse_parameter_type = usagi::type::mouse::default_parameter<ValueType>;
  using mouse_traits = typename usagi::type::mouse_traits<mouse_parameter_type>;
  void event(typename mouse_traits::on_down_type);
  void event(typename mouse_traits::on_drag_type);
  void event(typename mouse_traits::on_up_type);
  void event(typename mouse_traits::on_over_type);
  // void event(typename mouse_traits::on_out_type);
};
