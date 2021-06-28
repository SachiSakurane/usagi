#pragma once

#include <type_traits>

namespace usagi::type
{
  struct mouse
  {
    template <class ValueType, class = std::enable_if_t<std::is_arithmetic_v<ValueType>>>
    struct on_down
    {
      ValueType x, y;
    };

    template <class ValueType, class = std::enable_if_t<std::is_arithmetic_v<ValueType>>>
    struct on_drag
    {
      ValueType x, y;
    };

    template <class ValueType, class = std::enable_if_t<std::is_arithmetic_v<ValueType>>>
    struct on_up
    {
      ValueType x, y;
    };

    template <class ValueType, class = std::enable_if_t<std::is_arithmetic_v<ValueType>>>
    struct on_over
    {
      ValueType x, y;
    };

    template <class ValueType>
    on_down(ValueType, ValueType) -> on_down<ValueType>;

    template <class ValueType>
    on_drag(ValueType, ValueType) -> on_drag<ValueType>;

    template <class ValueType>
    on_up(ValueType, ValueType) -> on_up<ValueType>;

    template <class ValueType>
    on_over(ValueType, ValueType) -> on_over<ValueType>;
  };
}
