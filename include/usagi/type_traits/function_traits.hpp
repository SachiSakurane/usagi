#pragma once

#include <tuple>

namespace usagi::type_traits {
namespace detail {
  template <class R, class... Args>
  struct function_traits_impl {
    using result_type = R;
    static constexpr size_t arity = sizeof...(Args);
    using arguments_tuple = std::tuple<Args...>;

    template <size_t Index>
    using argument_type = std::tuple_element_t<Index, arguments_tuple>;
  };
} // namespace detail

template <class Functor>
struct function_traits : function_traits<decltype(&Functor::operator())> {};

template <class R, class... Args>
struct function_traits<R(Args...)> : detail::function_traits_impl<R, Args...> {};

template <class R, class... Args>
struct function_traits<R (*)(Args...)> : detail::function_traits_impl<R, Args...> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...)> : detail::function_traits_impl<R, Args...> {};

template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const> : detail::function_traits_impl<R, Args...> {};

} // namespace usagi::type_traits
