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
    struct mouse_traits
    {
      using on_down = on_down<ValueType>;
      using on_drag = on_drag<ValueType>;
      using on_up = on_up<ValueType>;
      using on_over = on_over<ValueType>;
    };
  };
}
