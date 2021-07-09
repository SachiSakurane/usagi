#pragma once

#include <cassert>

#include <usagi/utility/arithmetic.hpp>
#include <usagi/utility/mono_tuple.hpp>
#include <usagi/variable/variable_traits.hpp>

namespace usagi::geometry {
/**
 * size はマイナスを許容しない
 */
template <usagi::utility::arithmetic Type> struct size {
  using value_type = typename usagi::variable_traits<Type>::value_type;
  using variable_type = typename usagi::variable_traits<Type>::variable_type;

  constexpr size() : width_{}, height_{} {}
  constexpr size(variable_type w, variable_type h) : width_{w}, height_{h} {}

  value_type width() const {
    decltype(auto) w = width_();
    assert(w >= 0);
    return w;
  }

  value_type height() const {
    decltype(auto) h = height_();
    assert(h >= 0);
    return h;
  }

  std::pair<value_type, value_type> operator()() const {
    return {width(), height()};
  }

  size<value_type> duplicate() const {
    return size<value_type>{width(), height()};
  }

private:
  variable_type width_, height_;
};

/**
 * tuple特殊化
 */
template <usagi::utility::arithmetic Type> struct tupled_size {
  using value_type = Type;
  using pair_type = usagi::utility::mono_tuple<value_type, 2>;
  using size_type = typename usagi::variable_traits<pair_type>::value_type;
  using variable_type =
      typename usagi::variable_traits<pair_type>::variable_type;

  constexpr tupled_size() : functor{} {}
  constexpr tupled_size(variable_type s) : functor{s} {}

  value_type width() const {
    auto w = std::get<0>(functor());
    assert(w >= 0);
    return w;
  }

  value_type height() const {
    auto h = std::get<1>(functor());
    assert(h >= 0);
    return h;
  }

  size_type operator()() const {
    auto [w, h] = functor();
    assert(w >= 0);
    assert(h >= 0);
    return {w, h};
  }

  tupled_size<value_type> duplicate() const {
    return tupled_size<value_type>{functor()};
  }

private:
  variable_type functor;
};

} // namespace usagi::geometry
