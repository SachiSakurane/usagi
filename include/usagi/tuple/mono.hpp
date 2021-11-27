#pragma once

#include <utility>

namespace usagi::tuple {
namespace detail {
  template <class T, std::size_t Size, class... Args>
  struct mono_impl {
    typedef typename mono_impl<T, Size - 1, Args..., T>::type type;
  };

  template <class T, class... Args>
  struct mono_impl<T, 0, Args...> {
    typedef std::tuple<Args...> type;
  };
} // namespace detail

template <class T, std::size_t Size>
using mono = typename detail::mono_impl<T, Size>::type;
} // namespace usagi::tuple
