#pragma once

#include <usagi/geometry/size/size.h>

namespace usagi
{
  template <
      class SizeTypeA,
      class SizeTypeB,
      class = std::enable_if_t<std::is_same_v<typename SizeTypeA::value_type, typename SizeTypeB::value_type>>>
  inline constexpr bool operator==(const SizeTypeA &lhs, const SizeTypeB &rhs)
  {
    return lhs.width() == rhs.width() && lhs.height() == rhs.height();
  }

  template <
      class SizeTypeA,
      class SizeTypeB,
      class = std::enable_if_t<std::is_same_v<typename SizeTypeA::value_type, typename SizeTypeB::value_type>>>
  inline constexpr bool operator!=(const SizeTypeA &lhs, const SizeTypeB &rhs)
  {
    return !(lhs == rhs);
  }

  template <class SizeType>
  inline constexpr decltype(auto) operator+(typename SizeType::value_type &&lhs, const SizeType &rhs)
  {
    return usagi::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs + rhs.width(), lhs + rhs.height()); }};
  }

  template <class SizeType>
  inline constexpr decltype(auto) operator+(const SizeType &lhs, typename SizeType::value_type &&rhs)
  {
    return usagi::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() + rhs, lhs.height() + rhs); }};
  }

  template <
      class SizeTypeA,
      class SizeTypeB,
      class = std::enable_if_t<std::is_same_v<typename SizeTypeA::value_type, typename SizeTypeB::value_type>>>
  inline constexpr decltype(auto) operator+(const SizeTypeA &lhs, const SizeTypeB &rhs)
  {
    return usagi::paired_size<typename SizeTypeA::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() + rhs.width(), lhs.height() + rhs.height()); }};
  }

  template <class SizeType>
  inline constexpr decltype(auto) operator-(typename SizeType::value_type &&lhs, const SizeType &rhs)
  {
    return usagi::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs - rhs.width(), lhs - rhs.height()); }};
  }

  template <class SizeType>
  inline constexpr decltype(auto) operator-(const SizeType &lhs, typename SizeType::value_type &&rhs)
  {
    return usagi::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() - rhs, lhs.height() - rhs); }};
  }

  template <
      class SizeTypeA,
      class SizeTypeB,
      class = std::enable_if_t<std::is_same_v<typename SizeTypeA::value_type, typename SizeTypeB::value_type>>>
  inline constexpr decltype(auto) operator-(const SizeTypeA &lhs, const SizeTypeB &rhs)
  {
    return usagi::paired_size<typename SizeTypeA::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() - rhs.width(), lhs.height() - rhs.height()); }};
  }

  template <class SizeType>
  inline constexpr decltype(auto) operator*(typename SizeType::value_type &&lhs, const SizeType &rhs)
  {
    assert(lhs >= 0);
    return usagi::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs * rhs.width(), lhs * rhs.height()); }};
  }

  template <class SizeType>
  inline constexpr decltype(auto) operator*(const SizeType &lhs, typename SizeType::value_type &&rhs)
  {
    assert(rhs >= 0);
    return usagi::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() * rhs, lhs.height() * rhs); }};
  }

  template <
      class SizeTypeA,
      class SizeTypeB,
      class = std::enable_if_t<std::is_same_v<typename SizeTypeA::value_type, typename SizeTypeB::value_type>>>
  inline constexpr decltype(auto) operator*(const SizeTypeA &lhs, const SizeTypeB &rhs)
  {
    return usagi::paired_size<typename SizeTypeA::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() * rhs.width(), lhs.height() * rhs.height()); }};
  }

  template <class SizeType>
  inline constexpr decltype(auto) operator/(typename SizeType::value_type &&lhs, const SizeType &rhs)
  {
    assert(lhs >= 0);
    return usagi::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs / rhs.width(), lhs / rhs.height()); }};
  }

  template <class SizeType>
  inline constexpr decltype(auto) operator/(const SizeType &lhs, typename SizeType::value_type &&rhs)
  {
    assert(rhs > 0);
    return usagi::paired_size<typename SizeType::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() / rhs, lhs.height() / rhs); }};
  }

  template <
      class SizeTypeA,
      class SizeTypeB,
      class = std::enable_if_t<std::is_same_v<typename SizeTypeA::value_type, typename SizeTypeB::value_type>>>
  inline constexpr decltype(auto) operator/(const SizeTypeA &lhs, const SizeTypeB &rhs)
  {
    return usagi::paired_size<typename SizeTypeA::value_type>{
        [lhs, rhs]()
        { return std::make_tuple(lhs.width() / rhs.width(), lhs.height() / rhs.height()); }};
  }
}
