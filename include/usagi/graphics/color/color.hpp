#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/floating_point.hpp>
#include <usagi/tuple/mono.hpp>
#include <usagi/variable/variable_traits.hpp>

namespace usagi::graphics {
template <usagi::concepts::arithmetic Type>
struct basic_color {
  using value_type = Type;

  constexpr basic_color() : a_{}, r_{}, g_{}, b_{} {}
  constexpr basic_color(value_type a, value_type r, value_type g, value_type b)
      : a_{a}, r_{r}, g_{g}, b_{b} {
    assert(a >= 0);
    assert(r >= 0);
    assert(g >= 0);
    assert(b >= 0);
  }

  value_type alpha() const { return a_; }

  value_type red() const { return r_; }

  value_type green() const { return g_; }

  value_type blue() const { return b_; }

  usagi::tuple::mono_t<value_type, 4> operator()() const { return {alpha(), red(), green(), blue()}; }

private:
  value_type a_, r_, g_, b_;
};

template <usagi::concepts::floating_point FloatType>
using float_color = basic_color<FloatType>;

using color = basic_color<std::uint8_t>;

template <usagi::concepts::arithmetic Type>
struct variable_color {
  using value_type = typename usagi::variable_traits<Type>::value_type;
  using variable_type = typename usagi::variable_traits<Type>::variable_type;

  constexpr variable_color() : a_{}, r_{}, g_{}, b_{} {}
  constexpr variable_color(variable_type a, variable_type r, variable_type g, variable_type b)
      : a_{a}, r_{r}, g_{g}, b_{b} {}

  value_type red() const { return r_(); }

  value_type green() const { return g_(); }

  value_type blue() const { return b_(); }

  value_type alpha() const { return a_(); }

  usagi::tuple::mono_t<value_type, 4> operator()() const { return {a_(), r_(), g_(), b_()}; }

  variable_color<value_type> duplicate() const {
    return variable_color<value_type>{alpha(), red(), green(), blue()};
  }

private:
  variable_type a_, r_, g_, b_;
};
} // namespace usagi::graphics
