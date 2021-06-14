#pragma once

#include <usagi/geometry/size/size.h>

namespace usagi
{
  template <class Type>
  inline constexpr bool operator==(const usagi::size<Type> &lhs, const usagi::size<Type> &rhs)
  {
    return lhs.width() == rhs.width() && lhs.height() == rhs.height();
  }

  template <class Type>
  inline constexpr bool operator!=(const usagi::size<Type> &lhs, const usagi::size<Type> &rhs)
  {
    return !(lhs == rhs);
  }

  template <class Type>
  inline constexpr decltype(auto) operator+(typename usagi::size<Type>::value_type &&lhs, const usagi::size<Type> &rhs)
  {
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs + rhs.width(); },
        [lhs, rhs]()
        { return lhs + rhs.height(); }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator+(const usagi::size<Type> &lhs, typename usagi::size<Type>::value_type &&rhs)
  {
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs.width() + rhs; },
        [lhs, rhs]()
        { return lhs.height() + rhs; }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator+(const usagi::size<Type> &lhs, const usagi::size<Type> &rhs)
  {
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs.width() + rhs.width(); },
        [lhs, rhs]()
        { return lhs.height() + rhs.height(); }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator-(typename usagi::size<Type>::value_type &&lhs, const usagi::size<Type> &rhs)
  {
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs - rhs.width(); },
        [lhs, rhs]()
        { return lhs - rhs.height(); }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator-(const usagi::size<Type> &lhs, typename usagi::size<Type>::value_type &&rhs)
  {
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs.width() - rhs; },
        [lhs, rhs]()
        { return lhs.height() - rhs; }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator-(const usagi::size<Type> &lhs, const usagi::size<Type> &rhs)
  {
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs.width() - rhs.width(); },
        [lhs, rhs]()
        { return lhs.height() - rhs.height(); }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator*(typename usagi::size<Type>::value_type &&lhs, const usagi::size<Type> &rhs)
  {
    assert(lhs >= 0);
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs * rhs.width(); },
        [lhs, rhs]()
        { return lhs * rhs.height(); }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator*(const usagi::size<Type> &lhs, typename usagi::size<Type>::value_type &&rhs)
  {
    assert(rhs >= 0);
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs.width() * rhs; },
        [lhs, rhs]()
        { return lhs.height() * rhs; }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator*(const usagi::size<Type> &lhs, const usagi::size<Type> &rhs)
  {
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs.width() * rhs.width(); },
        [lhs, rhs]()
        { return lhs.height() * rhs.height(); }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator/(typename usagi::size<Type>::value_type &&lhs, const usagi::size<Type> &rhs)
  {
    assert(lhs >= 0);
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs / rhs.width(); },
        [lhs, rhs]()
        { return lhs / rhs.height(); }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator/(const usagi::size<Type> &lhs, typename usagi::size<Type>::value_type &&rhs)
  {
    assert(rhs > 0);
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs.width() / rhs; },
        [lhs, rhs]()
        { return lhs.height() / rhs; }};
  }

  template <class Type>
  inline constexpr decltype(auto) operator/(const usagi::size<Type> &lhs, const usagi::size<Type> &rhs)
  {
    return usagi::size<Type>{
        [lhs, rhs]()
        { return lhs.width() / rhs.width(); },
        [lhs, rhs]()
        { return lhs.height() / rhs.height(); }};
  }
}
