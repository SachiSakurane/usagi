#pragma once

#include <usagi/utility/arithmetic.hpp>
#include <usagi/utility/floating_point.hpp>

namespace usagi::concepts::geometry {
/**
 * sizeが表現可能
 */
template <class SizeType>
concept size_concept = usagi::utility::arithmetic<typename SizeType::value_type> &&
    requires(SizeType &s) {
  { s.width() } -> usagi::utility::arithmetic;
  { s.height() } -> usagi::utility::arithmetic;
};

template <class FloatSizeType>
concept float_size_concept = usagi::utility::floating_point<typename FloatSizeType::value_type> &&
    size_concept<FloatSizeType>;
} // namespace usagi::concepts::geometry
