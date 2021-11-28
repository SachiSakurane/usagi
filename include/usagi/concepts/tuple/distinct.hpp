#pragma once

#include <tuple>
#include <utility>

#include <usagi/tuple/erase.hpp>
#include <usagi/tuple/front.hpp>
#include <usagi/tuple/has.hpp>

namespace usagi::concepts::tuple {
namespace detail {
  template <class TupleType, size_t Size = std::tuple_size_v<TupleType>>
  class distinct_impl {
    using target = usagi::tuple::front_t<TupleType>;
    using sub_tuple = usagi::tuple::erase_front_t<TupleType>;

  public:
    static constexpr bool value =
        !usagi::tuple::has<target, sub_tuple>::value && distinct_impl<sub_tuple>::value;
  };

  template <class TupleType>
  struct distinct_impl<TupleType, 0> {
    static constexpr bool value = true;
  };
} // namespace detail

template <class TupleType>
concept distinct = detail::distinct_impl<TupleType>::value;
} // namespace usagi::concepts::tuple
