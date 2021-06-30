#pragma once

#include <usagi/type/mouse.h>

template <class ValueType>
struct Clickable
{
  using value_type = ValueType;
  using mouse_traits = typename usagi::type::mouse::mouse_traits<value_type>;
  void event(typename mouse_traits::on_down_type);
  void event(typename mouse_traits::on_drag_type);
  void event(typename mouse_traits::on_up_type);
  void event(typename mouse_traits::on_over_type);
};

template <class ValueType>
struct UnClickable
{
  using value_type = ValueType;
  using mouse_traits = typename usagi::type::mouse::mouse_traits<value_type>;
  void event(typename mouse_traits::on_down_type);
  void event(typename mouse_traits::on_drag_type);
  void event(typename mouse_traits::on_up_type);
  // void event(typename mouse_traits::on_over_type);
};