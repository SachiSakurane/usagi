#pragma once

#include <type_traits>

namespace usagi::concepts {
template <class Type>
concept arithmetic = std::is_arithmetic_v<Type>;
}
