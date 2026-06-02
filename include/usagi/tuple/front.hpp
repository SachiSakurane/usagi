#pragma once

#include <tuple>

namespace usagi::tuple {
/// Extracts the first element type from a tuple-like type.
///
/// @tparam TupleType Tuple-like input type.
template <class TupleType>
struct front {
  /// First element type of `TupleType`.
  using type = std::tuple_element_t<0, TupleType>;
};

/// Alias for the first element type of a tuple-like type.
///
/// @tparam TupleType Tuple-like input type.
template <class TupleType>
using front_t = typename front<TupleType>::type;
} // namespace usagi::tuple
