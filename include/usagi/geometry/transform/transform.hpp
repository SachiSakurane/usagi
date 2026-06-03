#pragma once

#include <usagi/concepts/floating_point.hpp>
#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/geometry/point/point.hpp>
#include <usagi/tuple/mono.hpp>

namespace usagi::geometry {
/// Two-dimensional transform with translation, rotation, scale, and transform origin.
///
/// @tparam Type Floating-point value type used for coordinates and the rotation angle.
template <usagi::concepts::floating_point Type>
struct transform {
  /// Transform value type.
  using value_type = Type;
  /// Point type used for translation, scale, and origin.
  using point_type = usagi::geometry::point<value_type>;

  /// Creates an identity transform.
  constexpr transform()
      : translation_{}, rotation_{}, scale_{static_cast<value_type>(1),
                                           static_cast<value_type>(1)},
        origin_{} {}

  /// Creates a transform from translation, rotation, scale, and origin.
  ///
  /// @param translation Translation applied in the parent coordinate system.
  /// @param rotation Rotation angle in radians.
  /// @param scale Scale factors for x and y.
  /// @param origin Transform origin in the local coordinate system.
  constexpr transform(const usagi::concepts::geometry::point_concept auto &translation,
                      value_type rotation,
                      const usagi::concepts::geometry::point_concept auto &scale,
                      const usagi::concepts::geometry::point_concept auto &origin)
      : translation_{translation.x(), translation.y()}, rotation_{rotation},
        scale_{scale.x(), scale.y()}, origin_{origin.x(), origin.y()} {}

  /// Returns the translation component.
  ///
  /// @return Stored translation point.
  constexpr point_type translation() const { return translation_; }

  /// Returns the rotation component.
  ///
  /// @return Stored rotation angle in radians.
  constexpr value_type rotation() const { return rotation_; }

  /// Returns the scale component.
  ///
  /// @return Stored scale factors for x and y.
  constexpr point_type scale() const { return scale_; }

  /// Returns the transform origin.
  ///
  /// @return Stored origin point in local coordinates.
  constexpr point_type origin() const { return origin_; }

  /// Returns the transform as
  /// `(translation.x, translation.y, rotation, scale.x, scale.y, origin.x, origin.y)`.
  ///
  /// @return Tuple containing the transform components.
  constexpr usagi::tuple::mono_t<value_type, 7> operator()() const {
    return {translation_.x(), translation_.y(), rotation_, scale_.x(),
            scale_.y(),       origin_.x(),      origin_.y()};
  }

  /// Returns a value-backed copy of this transform.
  ///
  /// @return New `transform` with the same translation, rotation, scale, and origin.
  constexpr transform<value_type> duplicate() const {
    return transform<value_type>{translation_, rotation_, scale_, origin_};
  }

private:
  point_type translation_;
  value_type rotation_;
  point_type scale_;
  point_type origin_;
};
} // namespace usagi::geometry
