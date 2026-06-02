#pragma once

#include <tuple>

namespace usagi::tuple {
/// Extracts the last element type from a tuple-like type.
///
/// @tparam TupleType Tuple-like input type.
template <class TupleType>
struct back {
  /// Last element type of `TupleType`.
  using type = std::tuple_element_t<std::tuple_size_v<TupleType> - 1, TupleType>;
};

/// Alias for the last element type of a tuple-like type.
///
/// @tparam TupleType Tuple-like input type.
template <class TupleType>
using back_t = typename back<TupleType>::type;
} // namespace usagi::tuple
