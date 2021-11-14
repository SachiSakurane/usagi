#pragma once

#include <functional>
#include <type_traits>

namespace usagi::concepts {
template <class F, class... Args>
concept invocable = requires(F &&f, Args &&...args) {
  std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
};

template <class F, class... Args>
concept regular_invocable = invocable<F, Args...>;
} // namespace usagi::utility
