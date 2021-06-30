#pragma once

#include <cassert>

#include <usagi/geometry/point.h>
#include <usagi/geometry/size.h>
#include <usagi/utility/arithmetic.h>

namespace usagi::geometry
{
  template <usagi::utility::arithmetic Type>
  struct rect
  {
  public:
    using value_type = typename usagi::variable_traits<Type>::value_type;
    using variable_type = typename usagi::variable_traits<Type>::variable_type;
    using size_type = usagi::geometry::size<value_type>;
    using point_type = usagi::geometry::point<value_type>;

    constexpr rect() : left{}, top{}, right{}, bottom{} {}
    constexpr rect(variable_type l, variable_type t, variable_type r, variable_type b) : left{l}, top{t}, right{r}, bottom{b} {}
    constexpr explicit rect(const size_type &size) : rect(point_type{}, size) {}
    constexpr rect(const point_type &point, const size_type &size)
        : left{[point]()
               { return point.x(); }},
          top{[point]()
              { return point.y(); }},
          right([size, point]()
                { return point.x() + size.width(); }),
          bottom{[size, point]()
                 { return point.y() + size.height(); }} {}

    decltype(auto) l() const
    {
      decltype(auto) v = left();
      assert(v <= right());
      return v;
    }

    decltype(auto) t() const
    {
      decltype(auto) v = top();
      assert(v <= bottom());
      return v;
    }

    decltype(auto) r() const
    {
      decltype(auto) v = right();
      assert(left() <= v);
      return v;
    }

    decltype(auto) b() const
    {
      decltype(auto) v = bottom();
      assert(top() <= v);
      return v;
    }

    size_type size() const
    {
      return size_type{[r = this->right, l = this->left]()
                       { return r() - l(); },
                       [b = this->bottom, t = this->top]()
                       { return b() - t(); }};
    }
    point_type center() const { return point_type{size() / static_cast<value_type>(2)}; }
    rect<value_type> duplicate() const { return rect<value_type>{left(), top(), right(), bottom()}; }

  private:
    variable_type left, top, right, bottom;
  };

  template <usagi::utility::arithmetic Type>
  rect(const usagi::geometry::size<Type> &) -> rect<Type>;

  template <usagi::utility::arithmetic Type>
  rect(const usagi::geometry::point<Type> &, const usagi::geometry::size<Type> &) -> rect<Type>;
}
