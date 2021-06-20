#pragma once

#include <functional>
#include <type_traits>

namespace usagi
{
  template <class ValueType>
  struct variable
  {
    using value_type = ValueType;

    variable() : functor{
                     []()
                     { return static_cast<value_type>(0); }} {}

    variable(const value_type& v) : functor{
                                 [v]()
                                 { return v; }} {}

    template <class FunctionType, class = std::enable_if_t<std::is_same_v<ValueType, std::invoke_result_t<FunctionType>>>>
    variable(FunctionType &&f) : functor{std::move(f)} {}

    decltype(auto) operator()() const
    {
      return functor();
    }

  private:
    std::function<value_type()> functor;
  };

  template <class ValueType>
  variable(const ValueType&) -> variable<ValueType>;

  template <class FunctionType>
  variable(FunctionType &&) -> variable<std::invoke_result_t<FunctionType>>;
}
