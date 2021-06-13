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

    size() : width_{}, height_{} {}
    size(variable_type w, variable_type h) : width_{w}, height_{h} {}

    decltype(auto) width() const
    {
      decltype(auto) w = width_();
      assert(w > 0);
      return w;
    }

    decltype(auto) height() const
    {
      decltype(auto) h = height_();
      assert(h > 0);
      return h;
    }

    decltype(auto) duplicate() const { return size<Type>{width(), height()}; }

  private:
    variable_type width_, height_;
  };
}
