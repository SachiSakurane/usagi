#pragma once

#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/geometry/size/size.hpp>

namespace usagi::geometry
{
  inline constexpr bool operator==(const usagi::concepts::geometry::size_concept auto &lhs, const usagi::concepts::geometry::size_concept auto &rhs)
  {
    return lhs.width() == rhs.width() && lhs.height() == rhs.height();
  }

  inline constexpr bool operator!=(const usagi::concepts::geometry::size_concept auto &lhs, const usagi::concepts::geometry::size_concept auto &rhs)
  {
    return !(lhs == rhs);
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator+(typename SizeType::value_type &&lhs, const SizeType &rhs)
  {
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs + rhs.width(), lhs + rhs.height()); }};
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator+(const SizeType &lhs, typename SizeType::value_type &&rhs)
  {
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() + rhs, lhs.height() + rhs); }};
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator+(const SizeType &lhs, const SizeType &rhs)
  {
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() + rhs.width(), lhs.height() + rhs.height()); }};
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator-(typename SizeType::value_type &&lhs, const SizeType &rhs)
  {
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs - rhs.width(), lhs - rhs.height()); }};
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator-(const SizeType &lhs, typename SizeType::value_type &&rhs)
  {
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() - rhs, lhs.height() - rhs); }};
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator-(const SizeType &lhs, const SizeType &rhs)
  {
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() - rhs.width(), lhs.height() - rhs.height()); }};
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator*(typename SizeType::value_type &&lhs, const SizeType &rhs)
  {
    assert(lhs >= 0);
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs * rhs.width(), lhs * rhs.height()); }};
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator*(const SizeType &lhs, typename SizeType::value_type &&rhs)
  {
    assert(rhs >= 0);
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() * rhs, lhs.height() * rhs); }};
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator*(const SizeType &lhs, const SizeType &rhs)
  {
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() * rhs.width(), lhs.height() * rhs.height()); }};
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator/(typename SizeType::value_type &&lhs, const SizeType &rhs)
  {
    assert(lhs >= 0);
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs / rhs.width(), lhs / rhs.height()); }};
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator/(const SizeType &lhs, typename SizeType::value_type &&rhs)
  {
    assert(rhs > 0);
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() / rhs, lhs.height() / rhs); }};
  }

  template <usagi::concepts::geometry::size_concept SizeType>
  inline constexpr decltype(auto) operator/(const SizeType &lhs, const SizeType &rhs)
  {
    return usagi::geometry::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() / rhs.width(), lhs.height() / rhs.height()); }};
  }
}
