#pragma once

#include <type_traits>

#include <usagi/utility/arithmetic.hpp>

namespace usagi::type {
struct mouse {
  template <usagi::utility::arithmetic ValueType>
  struct default_parameter {
    ValueType x, y;
  };

  template <class ParameterType>
  struct on_down : ParameterType {
    on_down() = default;
    template <class... Args>
    explicit on_down(Args &&...args) : ParameterType{std::forward<Args>(args)...} {}
  };

  template <class ParameterType>
  struct on_drag : ParameterType {
    on_drag() = default;
    template <class... Args>
    explicit on_drag(Args &&...args) : ParameterType{std::forward<Args>(args)...} {}
  };

  template <class ParameterType>
  struct on_up : ParameterType {
    on_up() = default;
    template <class... Args>
    explicit on_up(Args &&...args) : ParameterType{std::forward<Args>(args)...} {}
  };

  template <class ParameterType>
  struct on_over : ParameterType {
    on_over() = default;
    template <class... Args>
    explicit on_over(Args &&...args) : ParameterType{std::forward<Args>(args)...} {}
  };

  template <class ParameterType>
  struct on_out : ParameterType {
    on_out() = default;
    template <class... Args>
    explicit on_out(Args &&...args) : ParameterType{std::forward<Args>(args)...} {}
  };
};

template <class ParameterType>
struct mouse_traits {
  using on_down_type = mouse::on_down<ParameterType>;
  using on_drag_type = mouse::on_drag<ParameterType>;
  using on_up_type = mouse::on_up<ParameterType>;
  using on_over_type = mouse::on_over<ParameterType>;
  using on_out_type = mouse::on_out<ParameterType>;
};
} // namespace usagi::type
