#pragma once

#include <type_traits>

namespace usagi::utility {
/// Alias for `std::is_invocable_r` with function, return, and argument types grouped by name.
///
/// @tparam F Callable type to test.
/// @tparam R Expected return type.
/// @tparam ArgsTypes Argument types used for invocation.
template <class F, class R, class... ArgsTypes>
using is_invocable_f_r_args = std::is_invocable_r<R, F, ArgsTypes...>;

/// Convenience value for `is_invocable_f_r_args<F, R, ArgsTypes...>::value`.
///
/// @tparam F Callable type to test.
/// @tparam R Expected return type.
/// @tparam ArgsTypes Argument types used for invocation.
template <class F, class R, class... ArgsTypes>
inline constexpr bool is_invocable_f_r_args_v = is_invocable_f_r_args<F, R, ArgsTypes...>::value;
} // namespace usagi::utility
