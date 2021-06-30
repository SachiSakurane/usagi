#pragma once

#include <usagi/geometry/size/size.h>

namespace usagi::geometry
{
  template <class Type, class = std::enable_if_t<std::is_arithmetic_v<Type>>>
  struct point
  {
    using value_type = typename usagi::variable_traits<Type>::value_type;
    using variable_type = typename usagi::variable_traits<Type>::variable_type;

    constexpr point() : x_{}, y_{} {}
    constexpr explicit point(const usagi::geometry::size<Type> &s) : x_{[s]()
                                                                        { return s.width(); }},
                                                                     y_{[s]()
                                                                        { return s.height(); }} {}
    constexpr point(variable_type x, variable_type y) : x_{x}, y_{y} {}

    template <class LocalType>
    constexpr explicit point(LocalType t) : x_{t.x}, y_{t.y} {}

    value_type x() const { return x_(); }
    value_type y() const { return y_(); }

    point<value_type> duplicate() const { return point<value_type>{x(), y()}; }

  private:
    variable_type x_, y_;
  };

  template <class Type>
  point(const usagi::geometry::size<Type> &) -> point<Type>;

  /**
   * pair特殊化
  */
  template <class Type, class = std::enable_if_t<std::is_arithmetic_v<Type>>>
  struct paired_point
  {
    using value_type = Type;
    using pair_type = usagi::utility::mono_tuple<value_type, 2>;
    using size_type = typename usagi::variable_traits<pair_type>::value_type;
    using variable_type = typename usagi::variable_traits<pair_type>::variable_type;

    constexpr paired_point() : functor{} {}
    constexpr paired_point(variable_type s) : functor{s} {}

    value_type x() const
    {
      return std::get<0>(functor());
    }

    value_type y() const
    {
      return std::get<1>(functor());
    }

    paired_point<value_type> duplicate() const { return paired_point<value_type>{functor()}; }

  private:
    variable_type functor;
  };
}
