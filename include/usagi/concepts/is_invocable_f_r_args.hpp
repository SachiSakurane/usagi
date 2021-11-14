#pragma once

#include <type_traits>

namespace usagi::utility {
template <class F, class R, class... ArgsTypes>
using is_invocable_f_r_args = std::is_invocable_r<R, F, ArgsTypes...>;

template <class F, class R, class... ArgsTypes>
inline constexpr bool is_invocable_f_r_args_v = is_invocable_f_r_args<F, R, ArgsTypes...>::value;
} // namespace usagi::utility
