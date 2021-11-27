#pragma once

#include <tuple>
#include <utility>

namespace usagi::tuple {
namespace detail {
  template <class TupleType, size_t Target, class Indexes>
  struct erase_impl {};

  template <class TupleType, size_t Target, size_t... Indexes>
  struct erase_impl<TupleType, Target, std::index_sequence<Indexes...>> {
    using type =
        std::tuple<std::tuple_element_t<(Indexes < Target ? Indexes : Indexes + 1), TupleType>...>;
  };
} // namespace detail

template <size_t Index, class TupleType>
struct erase {
  using type =
      typename detail::erase_impl<TupleType, Index,
                                  std::make_index_sequence<std::tuple_size_v<TupleType> - 1>>::type;
};

template <size_t Index, class TupleType>
using erase_t = typename erase<Index, TupleType>::type;

} // namespace usagi::tuple