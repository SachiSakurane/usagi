#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/geometry/point.hpp>
#include <usagi/geometry/size.hpp>

#include <type_traits>

namespace usagi::geometry {
/// Axis-aligned rectangle represented by left, top, right, and bottom edges.
///
/// @tparam Type Arithmetic value type used for all edges.
template <usagi::concepts::arithmetic Type>
struct rect {
public:
  /// Edge value type.
  using value_type = Type;
  /// Size type derived from the rectangle value type.
  using size_type = usagi::geometry::size<value_type>;
  /// Point type derived from the rectangle value type.
  using point_type = usagi::geometry::point<value_type>;

  /// Creates an empty rectangle at the origin.
  constexpr rect() : left{}, top{}, right{}, bottom{} {}

  /// Creates a rectangle from its four edges.
  ///
  /// @param l Left edge.
  /// @param t Top edge.
  /// @param r Right edge.
  /// @param b Bottom edge.
  constexpr rect(value_type l, value_type t, value_type r, value_type b)
      : left{l}, top{t}, right{r}, bottom{b} {}

  /// Creates a rectangle at the origin with the given size.
  ///
  /// @param size Size-like object providing width and height.
  constexpr explicit rect(const concepts::geometry::size_concept auto &size)
      : rect(point_type{}, size) {}

  /// Creates a rectangle from its top-left point and size.
  ///
  /// @param point Point-like object used as the left/top origin.
  /// @param size Size-like object used to compute right and bottom edges.
  constexpr rect(const concepts::geometry::point_concept auto &point,
                 const concepts::geometry::size_concept auto &size)
      : left{point.x()}, top{point.y()}, right{point.x() + size.width()}, bottom{point.y() +
                                                                                 size.height()} {}

  /// Creates a rectangle from another rectangle-like object.
  ///
  /// @param r Rectangle-like object whose edges are copied.
  constexpr explicit rect(const concepts::geometry::rect_concept auto &r)
      : left{r.l()}, top{r.t()}, right{r.r()}, bottom{r.b()} {}

  /// Returns the left edge.
  ///
  /// @return Stored left edge.
  constexpr value_type l() const { return left; }

  /// Returns the top edge.
  ///
  /// @return Stored top edge.
  constexpr value_type t() const { return top; }

  /// Returns the right edge.
  ///
  /// @return Stored right edge.
  constexpr value_type r() const { return right; }

  /// Returns the bottom edge.
  ///
  /// @return Stored bottom edge.
  constexpr value_type b() const { return bottom; }

  /// Returns the rectangle size as `(right - left, bottom - top)`.
  ///
  /// @return Size computed from the rectangle edges.
  constexpr size_type size() const { return size_type{r() - l(), b() - t()}; }

  /// Returns the center point of the rectangle.
  ///
  /// @return Point at the midpoint of the horizontal and vertical edges.
  constexpr point_type center() const {
    return point_type{(r() + l()) / static_cast<value_type>(2),
                      (b() + t()) / static_cast<value_type>(2)};
  }

  /// Returns the rectangle as `(left, top, right, bottom)`.
  ///
  /// @return Tuple containing left, top, right, and bottom edges in that order.
  constexpr usagi::tuple::mono_t<value_type, 4> operator()() const {
    return {l(), t(), r(), b()};
  }

  /// Returns a value-backed copy of this rectangle.
  ///
  /// @return New `rect` with the same edges.
  constexpr rect<value_type> duplicate() const {
    return rect<value_type>{left, top, right, bottom};
  }

private:
  value_type left, top, right, bottom;
};

/// Deduces the edge value type when constructing a rectangle from a size-like object.
template <usagi::concepts::geometry::size_concept SizeType>
rect(const SizeType &) -> rect<typename SizeType::value_type>;

/// Deduces the edge value type when constructing a rectangle from point and size.
template <usagi::concepts::geometry::point_concept PointType,
          usagi::concepts::geometry::size_concept SizeType,
          class = std::enable_if_t<
              std::is_same_v<typename PointType::value_type, typename SizeType::value_type>>>
rect(const PointType &, const SizeType &) -> rect<typename SizeType::value_type>;

/// Lazily evaluated axis-aligned rectangle.
///
/// @tparam Type Arithmetic value type produced by the stored functor.
template <usagi::concepts::arithmetic Type>
struct variable_rect {
public:
  /// Edge value type.
  using value_type = typename usagi::variable_traits<Type>::value_type;
  /// Tuple type used to represent `(left, top, right, bottom)`.
  using pair_type = usagi::tuple::mono_t<value_type, 4>;
  /// Callable wrapper used to produce the current rectangle.
  using variable_type = typename usagi::variable_traits<pair_type>::variable_type;
  /// Lazily evaluated size type derived from the rectangle value type.
  using size_type = geometry::variable_size<value_type>;
  /// Lazily evaluated point type derived from the rectangle value type.
  using point_type = geometry::variable_point<value_type>;

  /// Creates a variable rectangle with a default-initialized functor.
  constexpr variable_rect() : functor{} {}

  /// Creates a variable rectangle from a callable or stored value wrapper.
  ///
  /// @param v Callable wrapper that evaluates to `(left, top, right, bottom)`.
  constexpr explicit variable_rect(variable_type v) : functor{v} {}

  /// Evaluates and returns the current left edge.
  ///
  /// @return Left edge produced by the stored functor.
  /// @pre The evaluated left edge must not be greater than the right edge.
  value_type l() const {
    auto v = std::get<0>(functor());
    assert(v <= std::get<2>(functor()));
    return v;
  }

  /// Evaluates and returns the current top edge.
  ///
  /// @return Top edge produced by the stored functor.
  /// @pre The evaluated top edge must not be greater than the bottom edge.
  value_type t() const {
    auto v = std::get<1>(functor());
    assert(v <= std::get<3>(functor()));
    return v;
  }

  /// Evaluates and returns the current right edge.
  ///
  /// @return Right edge produced by the stored functor.
  /// @pre The evaluated right edge must not be less than the left edge.
  value_type r() const {
    auto v = std::get<2>(functor());
    assert(std::get<0>(functor()) <= v);
    return v;
  }

  /// Evaluates and returns the current bottom edge.
  ///
  /// @return Bottom edge produced by the stored functor.
  /// @pre The evaluated bottom edge must not be less than the top edge.
  value_type b() const {
    auto v = std::get<3>(functor());
    assert(std::get<1>(functor()) <= v);
    return v;
  }

  /// Returns a lazy size computed from the current rectangle edges.
  ///
  /// @return Variable size whose width is `right - left` and height is `bottom - top`.
  size_type size() const {
    return size_type{[f = this->functor]() {
      auto [l, t, r, b] = f();
      return std::make_tuple(r - l, b - t);
    }};
  }

  /// Returns a lazy center point computed from the current rectangle edges.
  ///
  /// @return Variable point at the midpoint of the evaluated edges.
  point_type center() const {
    return point_type{[f = this->functor]() {
      auto [l, t, r, b] = f();
      return std::make_tuple((r + l) / static_cast<value_type>(2),
                             (b + t) / static_cast<value_type>(2));
    }};
  }

  /// Evaluates and returns the current rectangle as `(left, top, right, bottom)`.
  ///
  /// @return Tuple containing evaluated left, top, right, and bottom edges.
  /// @pre The evaluated edges must satisfy `left <= right` and `top <= bottom`.
  usagi::tuple::mono_t<value_type, 4> operator()() const {
    auto [l, t, r, b] = functor();
    assert(l <= r);
    assert(t <= b);
    return {l, t, r, b};
  }

  /// Evaluates this variable rectangle and returns a new variable rectangle storing that value.
  ///
  /// @return New `variable_rect` backed by the currently evaluated rectangle.
  variable_rect<value_type> duplicate() const { return variable_rect<value_type>{functor()}; }

private:
  variable_type functor;
};
} // namespace usagi::geometry
