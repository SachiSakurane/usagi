#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/tuple/mono.hpp>
#include <usagi/variable/variable_traits.hpp>

namespace usagi::geometry {
/// Two-dimensional coordinate.
///
/// @tparam Type Arithmetic value type used for both axes.
template <usagi::concepts::arithmetic Type>
struct point {
  /// Coordinate value type.
  using value_type = Type;

  /// Creates a point at the origin.
  constexpr point() : x_{}, y_{} {}

  /// Creates a point from a size by mapping width to x and height to y.
  ///
  /// @param s Size-like object whose width becomes x and height becomes y.
  constexpr explicit point(const usagi::concepts::geometry::size_concept auto &s)
      : x_{s.width()}, y_{s.height()} {}

  /// Creates a point from x and y coordinates.
  ///
  /// @param x Horizontal coordinate.
  /// @param y Vertical coordinate.
  constexpr point(value_type x, value_type y) : x_{x}, y_{y} {}

  /// Returns the horizontal coordinate.
  ///
  /// @return Stored x coordinate.
  constexpr value_type x() const { return x_; }

  /// Returns the vertical coordinate.
  ///
  /// @return Stored y coordinate.
  constexpr value_type y() const { return y_; }

  /// Returns the point as `(x, y)`.
  ///
  /// @return Tuple containing x followed by y.
  constexpr usagi::tuple::mono_t<value_type, 2> operator()() const { return {x_, y_}; }

  /// Returns a value-backed copy of this point.
  ///
  /// @return New `point` with the same x and y coordinates.
  constexpr point<value_type> duplicate() const { return point<value_type>{x_, y_}; }

private:
  value_type x_, y_;
};

/// Deduces the coordinate value type when constructing a point from a size-like object.
template <usagi::concepts::geometry::size_concept SizeType>
point(const SizeType &) -> point<typename SizeType::value_type>;

/// Lazily evaluated two-dimensional coordinate.
///
/// @tparam Type Arithmetic value type produced by the stored functor.
template <usagi::concepts::arithmetic Type>
struct variable_point {
  /// Coordinate value type.
  using value_type = Type;
  /// Tuple type used to represent `(x, y)`.
  using mono_type = usagi::tuple::mono_t<value_type, 2>;
  /// Callable wrapper used to produce the current point.
  using variable_type = typename usagi::variable_traits<mono_type>::variable_type;

  /// Creates a variable point with a default-initialized functor.
  constexpr variable_point() : functor{} {}

  /// Creates a variable point from a callable or stored value wrapper.
  ///
  /// @param s Callable wrapper that evaluates to `(x, y)`.
  constexpr variable_point(variable_type s) : functor{s} {}

  /// Evaluates and returns the current x coordinate.
  ///
  /// @return X coordinate produced by the stored functor.
  value_type x() const { return std::get<0>(functor()); }

  /// Evaluates and returns the current y coordinate.
  ///
  /// @return Y coordinate produced by the stored functor.
  value_type y() const { return std::get<1>(functor()); }

  /// Evaluates and returns the current point as `(x, y)`.
  ///
  /// @return Tuple containing the evaluated x followed by y.
  typename variable_type::value_type operator()() const { return {functor()}; }

  /// Evaluates this variable point and returns a new variable point storing that value.
  ///
  /// @return New `variable_point` backed by the currently evaluated point.
  variable_point<value_type> duplicate() const { return variable_point<value_type>{functor()}; }

private:
  variable_type functor;
};
} // namespace usagi::geometry
