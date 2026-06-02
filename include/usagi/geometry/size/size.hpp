#pragma once

#include <cassert>

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/tuple/mono.hpp>
#include <usagi/variable/variable_traits.hpp>

namespace usagi::geometry {
/// Two-dimensional extent with non-negative width and height.
///
/// @tparam Type Arithmetic value type used for both dimensions.
template <usagi::concepts::arithmetic Type>
struct size {
  /// Dimension value type.
  using value_type = Type;

  /// Creates a zero-sized extent.
  constexpr size() : width_{}, height_{} {}

  /// Creates an extent from width and height.
  ///
  /// @param w Width of the extent.
  /// @param h Height of the extent.
  /// @pre Both values must be non-negative.
  constexpr size(value_type w, value_type h) : width_{w}, height_{h} {
    assert(width_ >= 0);
    assert(height_ >= 0);
  }

  /// Returns the horizontal extent.
  ///
  /// @return Stored width.
  constexpr value_type width() const { return width_; }

  /// Returns the vertical extent.
  ///
  /// @return Stored height.
  constexpr value_type height() const { return height_; }

  /// Returns the extent as `(width, height)`.
  ///
  /// @return Tuple containing width followed by height.
  constexpr usagi::tuple::mono_t<value_type, 2> operator()() const {
    return {width_, height_};
  }

  /// Returns a value-backed copy of this extent.
  ///
  /// @return New `size` with the same width and height.
  constexpr size<value_type> duplicate() const { return size<value_type>{width_, height_}; }

private:
  value_type width_, height_;
};

/// Lazily evaluated two-dimensional extent.
///
/// @tparam Type Arithmetic value type produced by the stored functor.
template <usagi::concepts::arithmetic Type>
struct variable_size {
  /// Dimension value type.
  using value_type = Type;
  /// Tuple type used to represent `(width, height)`.
  using mono_type = usagi::tuple::mono_t<value_type, 2>;
  /// Concrete value type accepted by `usagi::variable_traits`.
  using size_type = typename usagi::variable_traits<mono_type>::value_type;
  /// Callable wrapper used to produce the current extent.
  using variable_type = typename usagi::variable_traits<mono_type>::variable_type;

  /// Creates a variable extent with a default-initialized functor.
  constexpr variable_size() : functor{} {}

  /// Creates a variable extent from a callable or stored value wrapper.
  ///
  /// @param s Callable wrapper that evaluates to `(width, height)`.
  constexpr explicit variable_size(variable_type s) : functor{s} {}

  /// Evaluates and returns the current width.
  ///
  /// @return Width produced by the stored functor.
  /// @pre The evaluated width must be non-negative.
  value_type width() const {
    auto w = std::get<0>(functor());
    assert(w >= 0);
    return w;
  }

  /// Evaluates and returns the current height.
  ///
  /// @return Height produced by the stored functor.
  /// @pre The evaluated height must be non-negative.
  value_type height() const {
    auto h = std::get<1>(functor());
    assert(h >= 0);
    return h;
  }

  /// Evaluates and returns the current extent as `(width, height)`.
  ///
  /// @return Tuple containing the evaluated width followed by height.
  /// @pre Both evaluated values must be non-negative.
  mono_type operator()() const {
    auto [w, h] = functor();
    assert(w >= 0);
    assert(h >= 0);
    return {w, h};
  }

  /// Evaluates this variable extent and returns a new variable extent storing that value.
  ///
  /// @return New `variable_size` backed by the currently evaluated extent.
  variable_size<value_type> duplicate() const { return variable_size<value_type>{functor()}; }

private:
  variable_type functor;
};

} // namespace usagi::geometry
