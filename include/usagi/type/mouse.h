#pragma once

#include <type_traits>

#include <usagi/utility/arithmetic.h>

namespace usagi::type
{
  struct mouse
  {
    template <usagi::utility::arithmetic ValueType>
    struct on_down
    {
      on_down() = default;
      on_down(ValueType _x, ValueType _y) : x{_x}, y{_y} {}

      ValueType x, y;
    };

    template <usagi::utility::arithmetic ValueType>
    struct on_drag
    {
      on_drag() = default;
      on_drag(ValueType _x, ValueType _y) : x{_x}, y{_y} {}

      ValueType x, y;
    };

    template <usagi::utility::arithmetic ValueType>
    struct on_up
    {
      on_up() = default;
      on_up(ValueType _x, ValueType _y) : x{_x}, y{_y} {}

      ValueType x, y;
    };

    template <usagi::utility::arithmetic ValueType>
    struct on_over
    {
      on_over() = default;
      on_over(ValueType _x, ValueType _y) : x{_x}, y{_y} {}

      ValueType x, y;
    };

    template <usagi::utility::arithmetic ValueType>
    struct mouse_traits
    {
      using on_down_type = on_down<ValueType>;
      using on_drag_type = on_drag<ValueType>;
      using on_up_type = on_up<ValueType>;
      using on_over_type = on_over<ValueType>;
    };
  };
}
