#pragma once

#include <cassert>

#include <usagi/variable/variable_traits.h>

namespace usagi
{
  /** 
   * size はマイナスを許容しない
  */
  template <class Type>
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

    size<value_type> duplicate() const { return size<value_type>{width(), height()}; }

  private:
    variable_type width_, height_;
  };
}
