#pragma once

#include <usagi/concepts/floating_point.hpp>

namespace usagi::math {
/// Euler's number.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType e = static_cast<FloatType>(2.71828182845904523536028747135266);

/// Circle constant pi.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType pi = static_cast<FloatType>(3.14159265358979323846264338327950288);

/// Twice pi.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType two_pi = pi<FloatType> * static_cast<FloatType>(2.0);

/// Half pi.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType half_pi = pi<FloatType> * static_cast<FloatType>(0.5);

/// Quarter pi.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType quarter_pi = pi<FloatType> * static_cast<FloatType>(0.25);

/// Reciprocal of pi.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType inv_pi = static_cast<FloatType>(1.0) / pi<FloatType>;

/// Reciprocal of twice pi.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType inv_two_pi = static_cast<FloatType>(1.0) / two_pi<FloatType>;

/// Reciprocal of half pi.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType inv_half_pi = static_cast<FloatType>(1.0) / half_pi<FloatType>;

/// Reciprocal of quarter pi.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType inv_quarter_pi = static_cast<FloatType>(1.0) / quarter_pi<FloatType>;

/// Square root of two.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType root_two = static_cast<FloatType>(1.41421356237309504880168872420969808);

/// Reciprocal of the square root of two.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType inv_root_two = static_cast<FloatType>(1.0) / root_two<FloatType>;

/// Natural logarithm of two.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType ln_two = static_cast<FloatType>(0.693147180559945309429);

/// Natural logarithm of ten.
///
/// @tparam FloatType Floating-point result type.
template <usagi::concepts::floating_point FloatType>
inline constexpr FloatType ln_ten = static_cast<FloatType>(2.30258509299404568404);
} // namespace usagi::math
