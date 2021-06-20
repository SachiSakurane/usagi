#pragma once

#include <usagi/variable/variable.h>

namespace usagi
{
  template <class ValueType>
  struct variable_traits
  {
    using value_type = ValueType;
    using variable_type = usagi::variable<value_type>;
  };
}
