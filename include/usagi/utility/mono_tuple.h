#pragma once

#include <utility>

namespace usagi::utility
{
  namespace detail {
    template <class T, std::size_t Size, class... Args>
    struct mono_tuple_impl
    {
      typedef typename mono_tuple_impl<T, Size - 1, Args..., T>::type type;
    };

    template <class T, class... Args>
    struct mono_tuple_impl<T, 0, Args...>
    {
      typedef std::tuple<Args...> type;
    };
  }

  template <class T, std::size_t Size>
  using mono_tuple = typename detail::mono_tuple_impl<T, Size>::type;
}
