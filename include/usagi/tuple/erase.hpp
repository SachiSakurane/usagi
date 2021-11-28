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

template <class TupleType, size_t Index>
struct erase {
  using type =
      typename detail::erase_impl<TupleType, Index,
                                  std::make_index_sequence<std::tuple_size_v<TupleType> - 1>>::type;
};

template <class TupleType>
struct erase_front {
  using type = typename erase<TupleType, 0>::type;
};

template <class TupleType>
struct erase_back {
  using type = typename erase<TupleType, std::tuple_size_v<TupleType> - 1>::type;
};

template <class TupleType, size_t Index>
using erase_t = typename erase<TupleType, Index>::type;

template <class TupleType>
using erase_front_t = typename erase_front<TupleType>::type;

template <class TupleType>
using erase_back_t = typename erase_back<TupleType>::type;

} // namespace usagi::tuple