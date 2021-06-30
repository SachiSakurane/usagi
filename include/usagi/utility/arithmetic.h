#pragma once

#include <type_traits>

namespace usagi::utility
{
  template <class Type>
  concept arithmetic = std::is_arithmetic_v<Type>;
}
