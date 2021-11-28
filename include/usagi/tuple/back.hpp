#pragma once

#include <tuple>

namespace usagi::tuple {
template <class TupleType>
struct back {
  using type = std::tuple_element_t<std::tuple_size_v<TupleType> - 1, TupleType>;
};

template <class TupleType>
using back_t = using back<TupleType>::type;
} // namespace usagi::tuple
