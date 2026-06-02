#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/floating_point.hpp>
#include <usagi/tuple/mono.hpp>
#include <usagi/variable/variable_traits.hpp>

namespace usagi::graphics {
/// ARGB color value.
///
/// @tparam Type Arithmetic channel value type.
template <usagi::concepts::arithmetic Type>
struct basic_color {
  /// Channel value type.
  using value_type = Type;

  /// Creates a color with all channels initialized to zero.
  constexpr basic_color() : a_{}, r_{}, g_{}, b_{} {}

  /// Creates a color from alpha, red, green, and blue channels.
  ///
  /// @param a Alpha channel.
  /// @param r Red channel.
  /// @param g Green channel.
  /// @param b Blue channel.
  /// @pre All channel values must be non-negative.
  constexpr basic_color(value_type a, value_type r, value_type g, value_type b)
      : a_{a}, r_{r}, g_{g}, b_{b} {
    assert(a >= 0);
    assert(r >= 0);
    assert(g >= 0);
    assert(b >= 0);
  }

  /// Returns the alpha channel.
  ///
  /// @return Stored alpha value.
  value_type alpha() const { return a_; }

  /// Returns the red channel.
  ///
  /// @return Stored red value.
  value_type red() const { return r_; }

  /// Returns the green channel.
  ///
  /// @return Stored green value.
  value_type green() const { return g_; }

  /// Returns the blue channel.
  ///
  /// @return Stored blue value.
  value_type blue() const { return b_; }

  /// Returns the color as `(alpha, red, green, blue)`.
  ///
  /// @return Tuple containing alpha, red, green, and blue in that order.
  usagi::tuple::mono_t<value_type, 4> operator()() const { return {alpha(), red(), green(), blue()}; }

private:
  value_type a_, r_, g_, b_;
};

/// Floating-point ARGB color alias.
///
/// @tparam FloatType Floating-point channel value type.
template <usagi::concepts::floating_point FloatType>
using float_color = basic_color<FloatType>;

/// 8-bit ARGB color alias.
using color = basic_color<std::uint8_t>;

/// Lazily evaluated ARGB color.
///
/// @tparam Type Arithmetic channel type or variable-compatible channel source.
template <usagi::concepts::arithmetic Type>
struct variable_color {
  /// Evaluated channel value type.
  using value_type = typename usagi::variable_traits<Type>::value_type;
  /// Callable wrapper used to produce a channel value.
  using variable_type = typename usagi::variable_traits<Type>::variable_type;

  /// Creates a variable color with default-initialized channel functors.
  constexpr variable_color() : a_{}, r_{}, g_{}, b_{} {}

  /// Creates a variable color from alpha, red, green, and blue channel sources.
  ///
  /// @param a Alpha channel source.
  /// @param r Red channel source.
  /// @param g Green channel source.
  /// @param b Blue channel source.
  constexpr variable_color(variable_type a, variable_type r, variable_type g, variable_type b)
      : a_{a}, r_{r}, g_{g}, b_{b} {}

  /// Evaluates and returns the current red channel.
  ///
  /// @return Red channel produced by the stored source.
  value_type red() const { return r_(); }

  /// Evaluates and returns the current green channel.
  ///
  /// @return Green channel produced by the stored source.
  value_type green() const { return g_(); }

  /// Evaluates and returns the current blue channel.
  ///
  /// @return Blue channel produced by the stored source.
  value_type blue() const { return b_(); }

  /// Evaluates and returns the current alpha channel.
  ///
  /// @return Alpha channel produced by the stored source.
  value_type alpha() const { return a_(); }

  /// Evaluates and returns the color as `(alpha, red, green, blue)`.
  ///
  /// @return Tuple containing evaluated alpha, red, green, and blue in that order.
  usagi::tuple::mono_t<value_type, 4> operator()() const { return {a_(), r_(), g_(), b_()}; }

  /// Evaluates this variable color and returns a new variable color storing that value.
  ///
  /// @return New `variable_color` backed by the currently evaluated channel values.
  variable_color<value_type> duplicate() const {
    return variable_color<value_type>{alpha(), red(), green(), blue()};
  }

private:
  variable_type a_, r_, g_, b_;
};
} // namespace usagi::graphics
