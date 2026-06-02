#pragma once

#include <functional>
#include <type_traits>

namespace usagi::concepts {
/// Matches callables that can be invoked with the given argument types.
///
/// @tparam F Callable type to test.
/// @tparam Args Argument types used for invocation.
template <class F, class... Args>
concept invocable = requires(F &&f, Args &&...args) {
  std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
};

/// Matches regular callables that can be invoked with the given argument types.
///
/// @tparam F Callable type to test.
/// @tparam Args Argument types used for invocation.
template <class F, class... Args>
concept regular_invocable = invocable<F, Args...>;
} // namespace usagi::utility
