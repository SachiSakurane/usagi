#pragma once

#include <cassert>

#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/geometry/point.hpp>
#include <usagi/geometry/size.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::geometry {
template <usagi::utility::arithmetic Type>
struct rect {
public:
  using value_type = Type;
  using size_type = usagi::geometry::size<value_type>;
  using point_type = usagi::geometry::point<value_type>;

  constexpr rect() : left{}, top{}, right{}, bottom{} {}

  constexpr rect(value_type l, value_type t, value_type r, value_type b)
      : left{l}, top{t}, right{r}, bottom{b} {
    assert(left <= right);
    assert(top <= bottom);
  }

  constexpr explicit rect(const concepts::geometry::size_concept auto &size)
      : rect(point_type{}, size) {}

  constexpr rect(const concepts::geometry::point_concept auto &point,
                 const concepts::geometry::size_concept auto &size)
      : left{point.x()}, top{point.y()}, right{point.x() + size.width()}, bottom{point.y() +
                                                                                 size.height()} {
    assert(left <= right);
    assert(top <= bottom);
  }

  constexpr explicit rect(const concepts::geometry::rect_concept auto &r)
      : left{r.l()}, top{r.t()}, right{r.r()}, bottom{r.b()} {}

  value_type l() const { return left; }
  value_type t() const { return top; }
  value_type r() const { return right; }
  value_type b() const { return bottom; }

  size_type size() const { return size_type{r() - l(), b() - t()}; }

  point_type center() const {
    return point_type{(r() + l()) / static_cast<value_type>(2),
                      (b() + t()) / static_cast<value_type>(2)};
  }

  usagi::utility::mono_tuple<value_type, 4> operator()() const { return {l(), t(), r(), b()}; }

private:
  value_type left, top, right, bottom;
};

template <usagi::concepts::geometry::size_concept SizeType>
rect(const SizeType &) -> rect<typename SizeType::value_type>;

template <usagi::concepts::geometry::point_concept PointType,
          usagi::concepts::geometry::size_concept SizeType,
          class = std::enable_if_t<
              std::is_same_v<typename PointType::value_type, typename SizeType::value_type>>>
rect(const PointType &, const SizeType &) -> rect<typename SizeType::value_type>;

/**
 * tupled特殊化
 */
template <usagi::utility::arithmetic Type>
struct variable_rect {
public:
  using value_type = typename usagi::variable_traits<Type>::value_type;
  using pair_type = utility::mono_tuple<value_type, 4>;
  using variable_type = typename usagi::variable_traits<pair_type>::variable_type;
  using size_type = geometry::size<value_type>;
  using point_type = geometry::point<value_type>;

  constexpr variable_rect() : functor{} {}
  constexpr explicit variable_rect(variable_type v) : functor{v} {}

  value_type l() const {
    auto v = std::get<0>(functor());
    assert(v <= std::get<2>(functor()));
    return v;
  }

  value_type t() const {
    auto v = std::get<1>(functor());
    assert(v <= std::get<3>(functor()));
    return v;
  }

  value_type r() const {
    auto v = std::get<2>(functor());
    assert(std::get<0>(functor()) <= v);
    return v;
  }

  value_type b() const {
    auto v = std::get<3>(functor());
    assert(std::get<1>(functor()) <= v);
    return v;
  }

  size_type size() const {
    return size_type{[f = this->functor]() { return std::get<2>(f()) - std::get<0>(f()); },
                     [f = this->functor]() { return std::get<3>(f()) - std::get<1>(f()); }};
  }

  point_type center() const {
    return point_type{[f = this->functor]() {
                        return (std::get<2>(f()) + std::get<0>(f())) / static_cast<value_type>(2);
                      },
                      [f = this->functor]() {
                        return (std::get<3>(f()) + std::get<1>(f())) / static_cast<value_type>(2);
                      }};
  }

  usagi::utility::mono_tuple<value_type, 4> operator()() const {
    auto [l, t, r, b] = functor();
    assert(l <= r);
    assert(t <= b);
    return {l, t, r, b};
  }

  variable_rect<value_type> duplicate() const { return variable_rect<value_type>{functor()}; }

private:
  variable_type functor;
};
} // namespace usagi::geometry
