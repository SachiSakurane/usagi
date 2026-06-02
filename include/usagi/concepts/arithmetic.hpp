#pragma once

#include <type_traits>

namespace usagi::concepts {
/// Matches arithmetic value types.
///
/// @tparam Type Type to test.
template <class Type>
concept arithmetic = std::is_arithmetic_v<Type>;
}
