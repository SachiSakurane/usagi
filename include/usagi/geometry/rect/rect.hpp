#pragma once

#include <cassert>

#include <usagi/geometry/point.hpp>
#include <usagi/geometry/size.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::geometry
{
  template <usagi::utility::arithmetic Type>
  struct rect
  {
  public:
    using value_type = typename usagi::variable_traits<Type>::value_type;
    using variable_type = typename usagi::variable_traits<value_type>::variable_type;
    using size_type = usagi::geometry::size<value_type>;
    using point_type = usagi::geometry::point<value_type>;

    constexpr rect() : left{}, top{}, right{}, bottom{} {}
    constexpr rect(variable_type l, variable_type t, variable_type r, variable_type b) : left{l}, top{t}, right{r}, bottom{b} {}
    constexpr explicit rect(const usagi::concepts::geometry::size_concept auto &size) : rect(point_type{}, size) {}
    constexpr rect(const usagi::concepts::geometry::point_concept auto &point, const usagi::concepts::geometry::size_concept auto &size)
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

  template <usagi::concepts::geometry::size_concept SizeType>
  rect(const SizeType &) -> rect<typename SizeType::value_type>;

  template <
      usagi::concepts::geometry::point_concept PointType,
      usagi::concepts::geometry::size_concept SizeType,
      class = std::enable_if_t<std::is_same_v<typename PointType::value_type, typename SizeType::value_type>>>
  rect(const PointType &, const SizeType &) -> rect<typename SizeType::value_type>;

  /**
   * tupled特殊化
  */
  template <usagi::utility::arithmetic Type>
  struct tupled_rect
  {
  public:
    using value_type = typename usagi::variable_traits<Type>::value_type;
    using pair_type = usagi::utility::mono_tuple<value_type, 4>;
    using variable_type = typename usagi::variable_traits<pair_type>::variable_type;
    using size_type = usagi::geometry::size<value_type>;
    using point_type = usagi::geometry::point<value_type>;

    constexpr tupled_rect() : functor{} {}
    constexpr tupled_rect(variable_type v) : functor{v} {}

    value_type l() const
    {
      auto v = std::get<0>(functor());
      assert(v <= std::get<2>(functor()));
      return v;
    }

    value_type t() const
    {
      auto v = std::get<1>(functor());
      assert(v <= std::get<3>(functor()));
      return v;
    }

    value_type r() const
    {
      auto v = std::get<2>(functor());
      assert(std::get<0>(functor()) <= v);
      return v;
    }

    value_type b() const
    {
      auto v = std::get<3>(functor());
      assert(std::get<1>(functor()) <= v);
      return v;
    }

    size_type size() const
    {
      return size_type{[f = this->functor]()
                       { return std::get<2>(f()) - std::get<0>(f()); },
                       [f = this->functor]()
                       { return std::get<3>(f()) - std::get<1>(f()); }};
    }
    point_type center() const { return point_type{size() / static_cast<value_type>(2)}; }
    tupled_rect<value_type> duplicate() const { return tupled_rect<value_type>{functor()}; }

  private:
    variable_type functor;
  };
}
