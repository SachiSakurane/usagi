#pragma once

#include <usagi/variable/variable_traits.h>
#include <usagi/utility/mono_tuple.h>

namespace usagi::graphics
{
  template <class Type, class = std::enable_if_t<std::is_arithmetic_v<Type>>>
  struct color
  {
    using value_type = typename usagi::variable_traits<Type>::value_type;
    using variable_type = typename usagi::variable_traits<Type>::variable_type;

    constexpr color() : r_{}, g_{}, b_{}, a_{} {}
    constexpr color(variable_type r, variable_type g, variable_type b, variable_type a) : r_{r}, g_{g}, b_{b}, a_{a} {}

    value_type r() const
    {
      return r_();
    }

    value_type g() const
    {
      return g_();
    }

    value_type b() const
    {
      return b_();
    }

    value_type a() const
    {
      return a_();
    }

    usagi::utility::mono_tuple<value_type, 4> operator()() const
    {
      return {r_(), g_(), b_(), a_()};
    }

    color<value_type> duplicate() const { return color<value_type>{r(), g(), b(), a()}; }

  private:
    variable_type r_, g_, b_, a_;
  };
}
