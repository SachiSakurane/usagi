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

template <class T, std::size_t Size>
struct mono {
  using type = typename detail::mono_impl<T, Size>::type;
};

template <class T, std::size_t Size>
using mono_t = typename mono<T, Size>::type;
} // namespace usagi::tuple
