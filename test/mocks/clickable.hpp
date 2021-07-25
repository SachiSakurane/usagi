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
};

template <class ValueType>
struct UnClickable {
  using mouse_parameter_type = usagi::type::mouse::default_parameter<ValueType>;
  using mouse_traits = typename usagi::type::mouse_traits<mouse_parameter_type>;
  void event(typename mouse_traits::on_down_type);
  void event(typename mouse_traits::on_drag_type);
  void event(typename mouse_traits::on_up_type);
  // void event(typename mouse_traits::on_over_type);
};
