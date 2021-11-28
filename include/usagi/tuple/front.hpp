#pragma once

#include <tuple>

namespace usagi::tuple {
template <class TupleType>
struct front {
  using type = std::tuple_element_t<0, TupleType>;
};

template <class TupleType>
using front_t = using front<TupleType>::type;
} // namespace usagi::tuple
