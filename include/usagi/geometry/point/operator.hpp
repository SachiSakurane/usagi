#pragma once

#include <usagi/concepts/geometry/point_concept.hpp>
#include <usagi/geometry/point/point.hpp>

namespace usagi::geometry {
inline constexpr bool
operator==(const usagi::concepts::geometry::point_concept auto &lhs,
           const usagi::concepts::geometry::point_concept auto &rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

inline constexpr bool
operator!=(const usagi::concepts::geometry::point_concept auto &lhs,
           const usagi::concepts::geometry::point_concept auto &rhs) {
  return !(lhs == rhs);
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto) operator+(typename PointType::value_type &&lhs,
                                          const PointType &rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() { return std::make_tuple(lhs + rhs.x(), lhs + rhs.y()); }};
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto)
operator+(const PointType &lhs, typename PointType::value_type &&rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() { return std::make_tuple(lhs.x() + rhs, lhs.y() + rhs); }};
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto) operator+(const PointType &lhs,
                                          const PointType &rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() {
        return std::make_tuple(lhs.x() + rhs.x(), lhs.y() + rhs.y());
      }};
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto) operator-(typename PointType::value_type &&lhs,
                                          const PointType &rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() { return std::make_tuple(lhs - rhs.x(), lhs - rhs.y()); }};
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto)
operator-(const PointType &lhs, typename PointType::value_type &&rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() { return std::make_tuple(lhs.x() - rhs, lhs.y() - rhs); }};
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto) operator-(const PointType &lhs,
                                          const PointType &rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() {
        return std::make_tuple(lhs.x() - rhs.x(), lhs.y() - rhs.y());
      }};
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto) operator*(typename PointType::value_type &&lhs,
                                          const PointType &rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() { return std::make_tuple(lhs * rhs.x(), lhs * rhs.y()); }};
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto)
operator*(const PointType &lhs, typename PointType::value_type &&rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() { return std::make_tuple(lhs.x() * rhs, lhs.y() * rhs); }};
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto) operator*(const PointType &lhs,
                                          const PointType &rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() {
        return std::make_tuple(lhs.x() * rhs.x(), lhs.y() * rhs.y());
      }};
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto) operator/(typename PointType::value_type &&lhs,
                                          const PointType &rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() { return std::make_tuple(lhs / rhs.x(), lhs / rhs.y()); }};
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto)
operator/(const PointType &lhs, typename PointType::value_type &&rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() { return std::make_tuple(lhs.x() / rhs, lhs.y() / rhs); }};
}

template <usagi::concepts::geometry::point_concept PointType>
inline constexpr decltype(auto) operator/(const PointType &lhs,
                                          const PointType &rhs) {
  return usagi::geometry::tupled_point<typename PointType::value_type>{
      [lhs, rhs]() {
        return std::make_tuple(lhs.x() / rhs.x(), lhs.y() / rhs.y());
      }};
}
} // namespace usagi::geometry
