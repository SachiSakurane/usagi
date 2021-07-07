#pragma once

#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/variable/variable_traits.hpp>
#include <usagi/utility/arithmetic.hpp>
#include <usagi/utility/mono_tuple.hpp>

namespace usagi::geometry
{
  template <usagi::utility::arithmetic Type>
  struct point
  {
    using value_type = typename usagi::variable_traits<Type>::value_type;
    using variable_type = typename usagi::variable_traits<Type>::variable_type;

    constexpr point() : x_{}, y_{} {}
    constexpr explicit point(const usagi::concepts::geometry::size_concept auto &s)
        : x_{[s]()
             { return s.width(); }},
          y_{[s]()
             { return s.height(); }} {}
    constexpr point(variable_type x, variable_type y) : x_{x}, y_{y} {}

    value_type x() const { return x_(); }
    value_type y() const { return y_(); }

    point<value_type> duplicate() const { return point<value_type>{x(), y()}; }

  private:
    variable_type x_, y_;
  };

  template <usagi::concepts::geometry::size_concept SizeType>
  point(const SizeType &) -> point<typename SizeType::value_type>;

  /**
   * pair特殊化
  */
  template <usagi::utility::arithmetic Type>
  struct paired_point
  {
    using value_type = Type;
    using pair_type = usagi::utility::mono_tuple<value_type, 2>;
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
