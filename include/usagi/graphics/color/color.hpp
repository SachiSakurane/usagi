#pragma once

#include <usagi/variable/variable_traits.hpp>
#include <usagi/utility/mono_tuple.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::graphics
{
  template <usagi::utility::arithmetic Type>
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

  /**
   * pair特殊化
  */
  template <usagi::utility::arithmetic Type>
  struct paired_color
  {
    using value_type = Type;
    using pair_type = usagi::utility::mono_tuple<value_type, 4>;
    using size_type = typename usagi::variable_traits<pair_type>::value_type;
    using variable_type = typename usagi::variable_traits<pair_type>::variable_type;

    constexpr paired_color() : functor{} {}
    constexpr paired_color(variable_type c) : functor{c} {}

    value_type r() const
    {
      return std::get<0>(functor());
    }

    value_type g() const
    {
      return std::get<1>(functor());
    }

    value_type b() const
    {
      return std::get<2>(functor());
    }

    value_type a() const
    {
      return std::get<3>(functor());
    }

    usagi::utility::mono_tuple<value_type, 4> operator()() const
    {
      return functor();
    }

    paired_color<value_type> duplicate() const { return paired_color<value_type>{functor()}; }

  private:
    variable_type functor;
  };
}
