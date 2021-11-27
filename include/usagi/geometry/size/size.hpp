#pragma once

#include <cassert>

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/tuple/mono.hpp>
#include <usagi/variable/variable_traits.hpp>

namespace usagi::geometry {
/**
 * size はマイナスを許容しない
 */
template <usagi::concepts::arithmetic Type>
struct size {
  using value_type = Type;

  constexpr size() : width_{}, height_{} {}
  constexpr size(value_type w, value_type h) : width_{w}, height_{h} {
    assert(width_ >= 0);
    assert(height_ >= 0);
  }

  constexpr value_type width() const { return width_; }
  constexpr value_type height() const { return height_; }

  constexpr usagi::tuple::mono<value_type, 2> operator()() const {
    return {width_, height_};
  }

private:
  value_type width_, height_;
};

/**
 * variable特殊化
 */
template <usagi::concepts::arithmetic Type>
struct variable_size {
  using value_type = Type;
  using pair_type = usagi::tuple::mono<value_type, 2>;
  using size_type = typename usagi::variable_traits<pair_type>::value_type;
  using variable_type = typename usagi::variable_traits<pair_type>::variable_type;

  constexpr variable_size() : functor{} {}
  constexpr explicit variable_size(variable_type s) : functor{s} {}

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

  usagi::tuple::mono<value_type, 2> operator()() const {
    auto [w, h] = functor();
    assert(w >= 0);
    assert(h >= 0);
    return {w, h};
  }

  variable_size<value_type> duplicate() const { return variable_size<value_type>{functor()}; }

private:
  variable_type functor;
};

} // namespace usagi::geometry
