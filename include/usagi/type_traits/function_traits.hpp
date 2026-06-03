#pragma once

#include <cstddef>
#include <tuple>

namespace usagi::type_traits {
namespace detail {
  /// Shared function signature metadata.
  ///
  /// @tparam R Function return type.
  /// @tparam Args Function argument types.
  template <class R, class... Args>
  struct function_traits_impl {
    /// Function return type.
    using result_type = R;
    /// Number of function arguments.
    static constexpr std::size_t arity = sizeof...(Args);
    /// Tuple containing all function argument types.
    using arguments_tuple = std::tuple<Args...>;

    /// Argument type at `Index`.
    ///
    /// @tparam Index Zero-based argument index.
    template <std::size_t Index>
    using argument_type = std::tuple_element_t<Index, arguments_tuple>;
  };
} // namespace detail

/// Extracts return and argument metadata from a callable type.
///
/// @tparam Functor Callable object type.
template <class Functor>
struct function_traits : function_traits<decltype(&Functor::operator())> {};

/// Extracts return and argument metadata from a function type.
///
/// @tparam R Function return type.
/// @tparam Args Function argument types.
template <class R, class... Args>
struct function_traits<R(Args...)> : detail::function_traits_impl<R, Args...> {};

/// Extracts return and argument metadata from a function pointer type.
///
/// @tparam R Function return type.
/// @tparam Args Function argument types.
template <class R, class... Args>
struct function_traits<R (*)(Args...)> : detail::function_traits_impl<R, Args...> {};

/// Extracts return and argument metadata from a mutable member function pointer.
///
/// @tparam C Owning class type.
/// @tparam R Function return type.
/// @tparam Args Function argument types.
template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...)> : detail::function_traits_impl<R, Args...> {};

/// Extracts return and argument metadata from a const member function pointer.
///
/// @tparam C Owning class type.
/// @tparam R Function return type.
/// @tparam Args Function argument types.
template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const> : detail::function_traits_impl<R, Args...> {};

} // namespace usagi::type_traits
