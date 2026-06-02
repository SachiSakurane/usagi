#pragma once

#include <tuple>
#include <utility>

namespace usagi::tuple {
namespace detail {
  template <class T, std::size_t Size, class... Args>
  struct mono_impl {
    using type = typename mono_impl<T, Size - 1, Args..., T>::type;
  };

  template <class T, class... Args>
  struct mono_impl<T, 0, Args...> {
    using type = std::tuple<Args...>;
  };
} // namespace detail

/// Builds a tuple type containing `Size` copies of `T`.
///
/// @tparam T Element type to repeat.
/// @tparam Size Number of tuple elements.
template <class T, std::size_t Size>
struct mono {
  /// Tuple type containing `Size` copies of `T`.
  using type = typename detail::mono_impl<T, Size>::type;
};

/// Alias for a tuple type containing `Size` copies of `T`.
///
/// @tparam T Element type to repeat.
/// @tparam Size Number of tuple elements.
template <class T, std::size_t Size>
using mono_t = typename mono<T, Size>::type;
} // namespace usagi::tuple
