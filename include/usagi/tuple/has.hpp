#pragma once

#include <tuple>
#include <type_traits>
#include <utility>

namespace usagi::tuple {
namespace detail {
  template <class TargetType, class Front, class... Types>
  struct has_impl_impl {
    static constexpr bool value =
        std::is_same_v<TargetType, Front> ? true : has_impl_impl<TargetType, Types...>::value;
  };

  template <class TargetType, class Last>
  struct has_impl_impl<TargetType, Last> {
    static constexpr bool value = std::is_same_v<TargetType, Last>;
  };

  template <class TargetType, class TupleType, class Indexes>
  struct has_impl {};

  template <class TargetType, class TupleType, size_t... Indexes>
  struct has_impl<TargetType, TupleType, std::index_sequence<Indexes...>> {
    static constexpr bool value =
        has_impl_impl<TargetType, std::tuple_element_t<Indexes, TupleType>...>::value;
  };

  template <class TargetType, class TupleType>
  struct has_impl<TargetType, TupleType, std::index_sequence<>> {
    static constexpr bool value = false;
  };

} // namespace detail

template <class TargetType, class TupleType>
struct has {
  static constexpr bool value =
      detail::has_impl<TargetType, TupleType,
                       std::make_index_sequence<std::tuple_size_v<TupleType>>>::value;
};

template <class TargetType, class TupleType>
using has_v = typename has<TargetType, TupleType>::value;
} // namespace usagi::tuple
