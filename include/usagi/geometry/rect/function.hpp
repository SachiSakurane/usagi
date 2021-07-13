#pragma once

#include <algorithm>

#include <usagi/concepts/geometry.hpp>
#include <usagi/geometry/rect/rect.hpp>

namespace usagi::geometry {
template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) from_left(const RectType &rect, typename RectType::value_type l) {
  return tupled_rect<typename RectType::value_type>{
      [rect, l]() { return std::make_tuple(l, rect.t(), rect.r(), rect.b()); }};
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) from_top(const RectType &rect, typename RectType::value_type t) {
  return tupled_rect<typename RectType::value_type>{
      [rect, t]() { return std::make_tuple(rect.l(), t, rect.r(), rect.b()); }};
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) from_right(const RectType &rect, typename RectType::value_type r) {
  return tupled_rect<typename RectType::value_type>{
      [rect, r]() { return std::make_tuple(rect.l(), rect.t(), r, rect.b()); }};
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) from_bottom(const RectType &rect, typename RectType::value_type b) {
  return tupled_rect<typename RectType::value_type>{
      [rect, b]() { return std::make_tuple(rect.l(), rect.t(), rect.r(), b); }};
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) from_width(const RectType &rect, typename RectType::value_type w) {
  return tupled_rect<typename RectType::value_type>{[rect, w]() {
    auto cx = rect.center().x();
    return std::make_tuple(cx - w * static_cast<typename RectType::value_type>(0.5f), rect.t(),
                           cx + w * static_cast<typename RectType::value_type>(0.5f), rect.b());
  }};
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) from_height(const RectType &rect, typename RectType::value_type h) {
  return tupled_rect<typename RectType::value_type>{[rect, h]() {
    auto cy = rect.center().y();
    return std::make_tuple(rect.l(), cy - h * static_cast<typename RectType::value_type>(0.5f),
                           rect.r(), cy + h * static_cast<typename RectType::value_type>(0.5f));
  }};
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) reduce_from_left(const RectType &rect,
                                                 typename RectType::value_type l) {
  return tupled_rect<typename RectType::value_type>{
      [rect, l]() { return std::make_tuple(rect.l() + l, rect.t(), rect.r(), rect.b()); }};
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) reduce_from_top(const RectType &rect,
                                                typename RectType::value_type t) {
  return tupled_rect<typename RectType::value_type>{
      [rect, t]() { return std::make_tuple(rect.l(), rect.t() + t, rect.r(), rect.b()); }};
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) reduce_from_right(const RectType &rect,
                                                  typename RectType::value_type r) {
  return tupled_rect<typename RectType::value_type>{
      [rect, r]() { return std::make_tuple(rect.l(), rect.t(), rect.r() - r, rect.b()); }};
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) reduce_from_bottom(const RectType &rect,
                                                   typename RectType::value_type b) {
  return tupled_rect<typename RectType::value_type>{
      [rect, b]() { return std::make_tuple(rect.l(), rect.t(), rect.r(), rect.b() - b); }};
}

inline constexpr bool contain(const concepts::geometry::rect_concept auto &r,
                              const concepts::geometry::point_concept auto &p) {
  return (r.l() <= p.x() && p.x() <= r.r()) && (r.t() <= p.y() && p.y() <= r.b());
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) padding(const RectType &rect, typename RectType::value_type v) {
  return tupled_rect<typename RectType::value_type>{[rect, v]() {
    auto l = rect.l() + v;
    auto t = rect.t() + v;
    auto r = rect.r() - v;
    auto b = rect.b() - v;
    bool w = l < r;
    bool h = t < b;
    return std::make_tuple(w ? l : (l + r) / static_cast<typename RectType::value_type>(2),
                           h ? t : (t + b) / static_cast<typename RectType::value_type>(2),
                           w ? r : (l + r) / static_cast<typename RectType::value_type>(2),
                           h ? b : (t + b) / static_cast<typename RectType::value_type>(2));
  }};
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) padding_width(const RectType &rect,
                                              typename RectType::value_type v) {
  return tupled_rect<typename RectType::value_type>{[rect, v]() {
    auto l = rect.l() + v;
    auto r = rect.r() - v;
    bool w = l < r;
    return std::make_tuple(
        w ? l : (l + r) / static_cast<typename RectType::value_type>(2), rect.t(),
        w ? r : (l + r) / static_cast<typename RectType::value_type>(2), rect.b());
  }};
}

template <concepts::geometry::rect_concept RectType>
inline constexpr decltype(auto) padding_height(const RectType &rect,
                                               typename RectType::value_type v) {
  return tupled_rect<typename RectType::value_type>{[rect, v]() {
    auto t = rect.t() + v;
    auto b = rect.b() - v;
    bool h = t < b;
    return std::make_tuple(
        rect.l(), h ? t : (t + b) / static_cast<typename RectType::value_type>(2), rect.r(),
        h ? b : (t + b) / static_cast<typename RectType::value_type>(2));
  }};
}
} // namespace usagi::geometry
