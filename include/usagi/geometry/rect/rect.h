#pragma once

#include <cassert>

#include <usagi/geometry/point.h>
#include <usagi/geometry/size.h>

namespace usagi
{
  template <class Type>
  struct rect
  {
  public:
    using value_type = typename usagi::variable_traits<Type>::value_type;
    using variable_type = typename usagi::variable_traits<Type>::variable_type;
    using size_type = usagi::size<value_type>;
    using point_type = usagi::point<value_type>;

    constexpr rect() : left{}, top{}, right{}, bottom{} {}
    constexpr rect(variable_type l, variable_type t, variable_type r, variable_type b) : left{l}, top{t}, right{r}, bottom{b} {}
    constexpr rect(const size_type &size) : rect(size, point_type{}) {}
    constexpr rect(const size_type &size, const point_type &point)
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
}
