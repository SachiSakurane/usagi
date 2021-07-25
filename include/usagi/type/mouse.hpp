#pragma once

#include <type_traits>

#include <usagi/utility/arithmetic.hpp>

namespace usagi::type {
struct mouse {
  template <usagi::utility::arithmetic ValueType>
  struct parameters {
    parameters() = default;
    parameters(ValueType _x, ValueType _y) : x{_x}, y{_y} {}

    ValueType x, y;
  };

  template <usagi::utility::arithmetic ValueType>
  struct on_down : parameters<ValueType> {
    on_down() = default;
    on_down(ValueType _x, ValueType _y) : parameters<ValueType>{_x, _y} {}
  };

  template <usagi::utility::arithmetic ValueType>
  struct on_drag : parameters<ValueType> {
    on_drag() = default;
    on_drag(ValueType _x, ValueType _y) : parameters<ValueType>{_x, _y} {}
  };

  template <usagi::utility::arithmetic ValueType>
  struct on_up : parameters<ValueType> {
    on_up() = default;
    on_up(ValueType _x, ValueType _y) : parameters<ValueType>{_x, _y} {}
  };
};

template <usagi::utility::arithmetic ValueType>
struct mouse_traits {
  using on_down_type = mouse::on_down<ValueType>;
  using on_drag_type = mouse::on_drag<ValueType>;
  using on_up_type = mouse::on_up<ValueType>;
};
} // namespace usagi::type
