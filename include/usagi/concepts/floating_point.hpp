#pragma once

#include <type_traits>

namespace usagi::concepts {
/// Matches floating-point value types.
///
/// @tparam Type Type to test.
template <class Type>
concept floating_point = std::is_floating_point_v<Type>;
}
