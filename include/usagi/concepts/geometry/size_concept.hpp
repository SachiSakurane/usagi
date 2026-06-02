#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/floating_point.hpp>

namespace usagi::concepts::geometry {
/// Matches size-like types with arithmetic width and height accessors.
///
/// @tparam SizeType Type to test.
template <class SizeType>
concept size_concept = requires(SizeType &s) {
  requires usagi::concepts::arithmetic<typename SizeType::value_type>;

  { s.width() } -> usagi::concepts::arithmetic;
  { s.height() } -> usagi::concepts::arithmetic;
};

/// Matches size-like types whose value type is floating-point.
///
/// @tparam FloatSizeType Type to test.
template <class FloatSizeType>
concept float_size_concept = usagi::concepts::floating_point<typename FloatSizeType::value_type> &&
    size_concept<FloatSizeType>;
} // namespace usagi::concepts::geometry
