#pragma once

#include <type_traits>

#include <usagi/utility/arithmetic.hpp>

namespace usagi::type {
struct mouse {
  template <usagi::utility::arithmetic ValueType>
  struct default_parameter {
    ValueType x, y, d;
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
    on_out(const ParameterType& p) : ParameterType{p} {}
  };

  template <class ParameterType>
  struct on_double : ParameterType {
    on_double() = default;
    template <class... Args>
    explicit on_double(Args &&...args) : ParameterType{std::forward<Args>(args)...} {}
  };

  template <class ParameterType>
  struct on_wheel : ParameterType {
    on_wheel() = default;
    template <class... Args>
    explicit on_wheel(Args &&...args) : ParameterType{std::forward<Args>(args)...} {}
  };
};

template <class ParameterType>
struct mouse_traits {
  using parameter_type = ParameterType;
  using on_down_type = mouse::on_down<ParameterType>;
  using on_drag_type = mouse::on_drag<ParameterType>;
  using on_up_type = mouse::on_up<ParameterType>;
  using on_over_type = mouse::on_over<ParameterType>;
  using on_out_type = mouse::on_out<ParameterType>;
  using on_double_type = mouse::on_double<ParameterType>;
  using on_wheel_type = mouse::on_wheel<ParameterType>;
};
} // namespace usagi::type
