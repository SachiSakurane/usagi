#pragma once

#include <cstddef>
#include <tuple>
#include <utility>

namespace usagi::tuple {
namespace detail {
  template <class TupleType, std::size_t Target, class Indexes>
  struct erase_impl {};

  template <class TupleType, std::size_t Target, std::size_t... Indexes>
  struct erase_impl<TupleType, Target, std::index_sequence<Indexes...>> {
    using type =
        std::tuple<std::tuple_element_t<(Indexes < Target ? Indexes : Indexes + 1), TupleType>...>;
  };
} // namespace detail

/// Removes the element at `Index` from a tuple-like type.
///
/// @tparam TupleType Tuple-like input type.
/// @tparam Index Element index to remove.
template <class TupleType, std::size_t Index>
struct erase {
  /// Tuple type with the selected element removed.
  using type =
      typename detail::erase_impl<TupleType, Index,
                                  std::make_index_sequence<std::tuple_size_v<TupleType> - 1>>::type;
};

/// Removes the first element from a tuple-like type.
///
/// @tparam TupleType Tuple-like input type.
template <class TupleType>
struct erase_front {
  /// Tuple type without the first element.
  using type = typename erase<TupleType, 0>::type;
};

/// Removes the last element from a tuple-like type.
///
/// @tparam TupleType Tuple-like input type.
template <class TupleType>
struct erase_back {
  /// Tuple type without the last element.
  using type = typename erase<TupleType, std::tuple_size_v<TupleType> - 1>::type;
};

/// Alias for a tuple-like type with the element at `Index` removed.
///
/// @tparam TupleType Tuple-like input type.
/// @tparam Index Element index to remove.
template <class TupleType, std::size_t Index>
using erase_t = typename erase<TupleType, Index>::type;

/// Alias for a tuple-like type without its first element.
///
/// @tparam TupleType Tuple-like input type.
template <class TupleType>
using erase_front_t = typename erase_front<TupleType>::type;

/// Alias for a tuple-like type without its last element.
///
/// @tparam TupleType Tuple-like input type.
template <class TupleType>
using erase_back_t = typename erase_back<TupleType>::type;

} // namespace usagi::tuple
