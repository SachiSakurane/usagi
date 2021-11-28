#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/tuple/mono.hpp>
#include <usagi/variable/variable_traits.hpp>

namespace usagi::geometry {
template <usagi::concepts::arithmetic Type>
struct point {
  using value_type = Type;

  constexpr point() : x_{}, y_{} {}
  constexpr explicit point(const usagi::concepts::geometry::size_concept auto &s)
      : x_{s.width()}, y_{s.height()} {}
  constexpr point(value_type x, value_type y) : x_{x}, y_{y} {}

  constexpr value_type x() const { return x_; }
  constexpr value_type y() const { return y_; }

  constexpr usagi::tuple::mono_t<value_type, 2> operator()() const { return {x_, y_}; }

private:
  value_type x_, y_;
};

template <usagi::concepts::geometry::size_concept SizeType>
point(const SizeType &) -> point<typename SizeType::value_type>;

/**
 * tuple特殊化
 */
template <usagi::concepts::arithmetic Type>
struct variable_point {
  using value_type = Type;
  using mono_type = usagi::tuple::mono_t<value_type, 2>;
  using variable_type = typename usagi::variable_traits<mono_type>::variable_type;

  constexpr variable_point() : functor{} {}
  constexpr variable_point(variable_type s) : functor{s} {}

  value_type x() const { return std::get<0>(functor()); }
  value_type y() const { return std::get<1>(functor()); }

  typename variable_type::value_type operator()() const { return {functor()}; }

  variable_point<value_type> duplicate() const { return variable_point<value_type>{functor()}; }

private:
  variable_type functor;
};
} // namespace usagi::geometry
