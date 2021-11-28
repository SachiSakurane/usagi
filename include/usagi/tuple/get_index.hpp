#pragma once

#include <tuple>
#include <utility>

#include <usagi/tuple/has.hpp>

namespace usagi::tuple {
namespace detail {
  template <class TargetType, class TupleType, size_t Index,
            bool Pred = std::is_same_v<TargetType, std::tuple_element_t<Index, TupleType>>>
  struct get_index_impl {
    static constexpr size_t value = get_index_impl<TargetType, TupleType, Index + 1>::value;
  };

  template <class TargetType, class TupleType, size_t Index>
  struct get_index_impl<TargetType, TupleType, Index, true> {
    static constexpr size_t value = Index;
  };
} // namespace detail

template <class TargetType, class TupleType>
requires usagi::tuple::has_v<TargetType, TupleType>
struct get_index {
  static constexpr size_t value = detail::get_index_impl<TargetType, TupleType, 0>::value;
};

template <class TargetType, class TupleType>
inline constexpr size_t get_index_v = get_index<TargetType, TupleType>::value;
} // namespace usagi::tuple
