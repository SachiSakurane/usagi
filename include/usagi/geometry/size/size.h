#pragma once

#include <cassert>

#include <usagi/variable/variable_traits.h>
#include <usagi/utility/mono_tuple.h>

namespace usagi
{
  /** 
   * size はマイナスを許容しない
  */
  template <class Type, class = std::enable_if_t<std::is_arithmetic_v<Type>>>
  struct size
  {
    using value_type = typename usagi::variable_traits<Type>::value_type;
    using variable_type = typename usagi::variable_traits<Type>::variable_type;

    constexpr size() : width_{}, height_{} {}
    constexpr size(variable_type w, variable_type h) : width_{w}, height_{h} {}

    value_type width() const
    {
      decltype(auto) w = width_();
      assert(w > 0);
      return w;
    }

    value_type height() const
    {
      decltype(auto) h = height_();
      assert(h > 0);
      return h;
    }

    std::pair<value_type, value_type> operator()() const
    {
      return {width(), height()};
    }

    size<value_type> duplicate() const { return size<value_type>{width(), height()}; }

  private:
    variable_type width_, height_;
  };

  /**
   * pair特殊化
  */
  template <class Type, class = std::enable_if_t<std::is_arithmetic_v<Type>>>
  struct paired_size
  {
    using value_type = Type;
    using pair_type = usagi::utility::mono_tuple<value_type, 2>;
    using size_type = typename usagi::variable_traits<pair_type>::value_type;
    using variable_type = typename usagi::variable_traits<pair_type>::variable_type;

    constexpr paired_size() : functor{} {}
    constexpr paired_size(variable_type s) : functor{s} {}

    value_type width() const
    {
      [[maybe_unused]] auto [w, _] = functor();
      assert(w > 0);
      return w;
    }

    value_type height() const
    {
      [[maybe_unused]] auto [_, h] = functor();
      assert(h > 0);
      return h;
    }

    size_type operator()() const
    {
      auto [w, h] = functor();
      assert(w > 0);
      assert(h > 0);
      return {w, h};
    }

    size<value_type> duplicate() const { return size<value_type>{functor()}; }

  private:
    variable_type functor;
  };

}
