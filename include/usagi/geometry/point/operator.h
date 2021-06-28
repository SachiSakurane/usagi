#pragma once

#include <usagi/concepts/geometry/point_concept.h>
#include <usagi/geometry/point/point.h>

namespace usagi
{
  inline constexpr bool operator==(const usagi::concepts::geometry::point_concept auto &lhs, const usagi::concepts::geometry::point_concept auto &rhs)
  {
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
  }

  inline constexpr bool operator!=(const usagi::concepts::geometry::point_concept auto &lhs, const usagi::concepts::geometry::point_concept auto &rhs)
  {
    return !(lhs == rhs);
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator+(typename usagi::point<Type>::value_type &&lhs, const usagi::point<Type> &rhs)
  {
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs + rhs.x(); },
        [lhs, rhs]()
        { return lhs + rhs.y(); }};
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator+(const usagi::point<Type> &lhs, typename usagi::point<Type>::value_type &&rhs)
  {
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs.x() + rhs; },
        [lhs, rhs]()
        { return lhs.y() + rhs; }};
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator+(const usagi::point<Type> &lhs, const usagi::point<Type> &rhs)
  {
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs.x() + rhs.x(); },
        [lhs, rhs]()
        { return lhs.y() + rhs.y(); }};
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator-(typename usagi::point<Type>::value_type &&lhs, const usagi::point<Type> &rhs)
  {
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs - rhs.x(); },
        [lhs, rhs]()
        { return lhs - rhs.y(); }};
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator-(const usagi::point<Type> &lhs, typename usagi::point<Type>::value_type &&rhs)
  {
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs.x() - rhs; },
        [lhs, rhs]()
        { return lhs.y() - rhs; }};
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator-(const usagi::point<Type> &lhs, const usagi::point<Type> &rhs)
  {
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs.x() - rhs.x(); },
        [lhs, rhs]()
        { return lhs.y() - rhs.y(); }};
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator*(typename usagi::point<Type>::value_type &&lhs, const usagi::point<Type> &rhs)
  {
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs * rhs.x(); },
        [lhs, rhs]()
        { return lhs * rhs.y(); }};
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator*(const usagi::point<Type> &lhs, typename usagi::point<Type>::value_type &&rhs)
  {
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs.x() * rhs; },
        [lhs, rhs]()
        { return lhs.y() * rhs; }};
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator*(const usagi::point<Type> &lhs, const usagi::point<Type> &rhs)
  {
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs.x() * rhs.x(); },
        [lhs, rhs]()
        { return lhs.y() * rhs.y(); }};
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator/(typename usagi::point<Type>::value_type &&lhs, const usagi::point<Type> &rhs)
  {
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs / rhs.x(); },
        [lhs, rhs]()
        { return lhs / rhs.y(); }};
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator/(const usagi::point<Type> &lhs, typename usagi::point<Type>::value_type &&rhs)
  {
    assert(rhs != 0);
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs.x() / rhs; },
        [lhs, rhs]()
        { return lhs.y() / rhs; }};
  }

  template <usagi::concepts::geometry::point_concept Type>
  inline constexpr decltype(auto) operator/(const usagi::point<Type> &lhs, const usagi::point<Type> &rhs)
  {
    return usagi::point<Type>{
        [lhs, rhs]()
        { return lhs.x() / rhs.x(); },
        [lhs, rhs]()
        { return lhs.y() / rhs.y(); }};
  }
}
