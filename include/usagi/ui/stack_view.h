#pragma once

#include <usagi/type/axis.h>

namespace usagi::ui
{
  struct variable {
    
  };

  struct spacing
  {
    variable space;
  };

  template <class ValueType, class AxisType>
  class stack_view
  {
  public:
    using value_type = ValueType;

    template <class... Args>
    stack_view(Args &&...args) {}

  private:
  };

  template <class ValueType>
  using horizontal_stack_view = stack_view<ValueType, type::horizontal_type_t>;

  template <class ValueType>
  using vertical_stack_view = stack_view<ValueType, type::vertical_type_t>;

}
