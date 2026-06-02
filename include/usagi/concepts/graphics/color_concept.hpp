#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/floating_point.hpp>

namespace usagi::concepts::graphics {
/// Matches color-like types with arithmetic alpha, red, green, and blue channels.
///
/// @tparam ColorType Type to test.
template <class ColorType>
concept basic_color_concept = requires(ColorType &c) {
  requires usagi::concepts::arithmetic<typename ColorType::value_type>;

  { c.alpha() } -> usagi::concepts::arithmetic;
  { c.red() } -> usagi::concepts::arithmetic;
  { c.green() } -> usagi::concepts::arithmetic;
  { c.blue() } -> usagi::concepts::arithmetic;
};

/// Matches color-like types whose channel value type is `std::uint8_t`.
///
/// @tparam ByteSizeType Type to test.
template <class ByteSizeType>
concept byte_color_concept = std::is_same_v<typename ByteSizeType::value_type, std::uint8_t> &&
    basic_color_concept<ByteSizeType>;

/// Matches color-like types whose channel value type is floating-point.
///
/// @tparam FloatSizeType Type to test.
template <class FloatSizeType>
concept float_color_concept = usagi::concepts::floating_point<typename FloatSizeType::value_type> &&
    basic_color_concept<FloatSizeType>;
} // namespace usagi::concepts::graphics
