#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/geometry/point/point.hpp>
#include <usagi/tuple/mono.hpp>

namespace usagi::geometry {
/// Two-dimensional transform with translation, rotation, and rotation origin.
///
/// @tparam Type Arithmetic value type used for coordinates and the rotation angle.
template <usagi::concepts::arithmetic Type>
struct transform {
  /// Transform value type.
  using value_type = Type;
  /// Point type used for translation and origin.
  using point_type = usagi::geometry::point<value_type>;

  /// Creates an identity transform.
  constexpr transform() : translation_{}, rotation_{}, origin_{} {}

  /// Creates a transform from translation, rotation, and origin.
  ///
  /// @param translation Translation applied in the parent coordinate system.
  /// @param rotation Rotation angle in radians.
  /// @param origin Rotation origin in the local coordinate system.
  constexpr transform(const usagi::concepts::geometry::point_concept auto &translation,
                      value_type rotation,
                      const usagi::concepts::geometry::point_concept auto &origin)
      : translation_{translation.x(), translation.y()}, rotation_{rotation},
        origin_{origin.x(), origin.y()} {}

  /// Returns the translation component.
  ///
  /// @return Stored translation point.
  constexpr point_type translation() const { return translation_; }

  /// Returns the rotation component.
  ///
  /// @return Stored rotation angle in radians.
  constexpr value_type rotation() const { return rotation_; }

  /// Returns the rotation origin.
  ///
  /// @return Stored origin point in local coordinates.
  constexpr point_type origin() const { return origin_; }

  /// Returns the transform as `(translation.x, translation.y, rotation, origin.x, origin.y)`.
  ///
  /// @return Tuple containing the transform components.
  constexpr usagi::tuple::mono_t<value_type, 5> operator()() const {
    return {translation_.x(), translation_.y(), rotation_, origin_.x(), origin_.y()};
  }

  /// Returns a value-backed copy of this transform.
  ///
  /// @return New `transform` with the same translation, rotation, and origin.
  constexpr transform<value_type> duplicate() const {
    return transform<value_type>{translation_, rotation_, origin_};
  }

private:
  point_type translation_;
  value_type rotation_;
  point_type origin_;
};
} // namespace usagi::geometry
