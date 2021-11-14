#pragma once

#include <type_traits>

namespace usagi::concepts {
template <class Type>
concept floating_point = std::is_floating_point_v<Type>;
}
