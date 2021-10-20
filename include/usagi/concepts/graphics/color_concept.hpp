#pragma once

#include <usagi/utility/arithmetic.hpp>
#include <usagi/utility/floating_point.hpp>

namespace usagi::concepts::graphics {
/**
 * colorが表現可能
 */
template <class ColorType>
concept basic_color_concept = usagi::utility::arithmetic<typename ColorType::value_type> &&
    requires(ColorType &c) {
  { c.alpha() } -> usagi::utility::arithmetic;
  { c.red() } -> usagi::utility::arithmetic;
  { c.green() } -> usagi::utility::arithmetic;
  { c.blue() } -> usagi::utility::arithmetic;
};

template <class FloatSizeType>
concept float_color_concept = usagi::utility::floating_point<typename FloatSizeType::value_type> &&
    basic_color_concept<FloatSizeType>;
} // namespace usagi::concepts::graphics
