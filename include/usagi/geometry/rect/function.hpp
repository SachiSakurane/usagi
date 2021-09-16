#pragma once

#include <algorithm>

#include <usagi/concepts/geometry.hpp>
#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/rect/rect.hpp>
#include <usagi/geometry/size/size.hpp>

namespace usagi::geometry {
template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) make_from_center(const usagi::geometry::point<ValueType> &center,
                                                 const usagi::geometry::size<ValueType> &size) {
  constexpr usagi::utility::arithmetic auto two = static_cast<ValueType>(2);
  return usagi::geometry::rect<ValueType>{
      center.x() - size.width() / two, center.y() - size.height() / two,
      center.x() + size.width() / two, center.y() + size.height() / two};
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) transform(const usagi::geometry::rect<ValueType> &rect, ValueType x,
                                          ValueType y) {
  return usagi::geometry::rect<ValueType>{rect.l() + x, rect.t() + y, rect.r() + x, rect.b() + y};
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) from_left(const usagi::geometry::rect<ValueType> &rect,
                                          ValueType l) {
  return usagi::geometry::rect<ValueType>{rect.l(), rect.t(), rect.l() + l, rect.b()};
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) from_top(const usagi::geometry::rect<ValueType> &rect,
                                         ValueType t) {
  return usagi::geometry::rect<ValueType>{rect.l(), rect.t(), rect.r(), rect.t() + t};
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) from_right(const usagi::geometry::rect<ValueType> &rect,
                                           ValueType r) {
  return usagi::geometry::rect<ValueType>{rect.r() - r, rect.t(), rect.r(), rect.b()};
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) from_bottom(const usagi::geometry::rect<ValueType> &rect,
                                            ValueType b) {
  return usagi::geometry::rect<ValueType>{rect.l(), rect.b() - b, rect.r(), rect.b()};
}

template <usagi::utility::floating_point ValueType>
inline constexpr decltype(auto) from_width(const usagi::geometry::rect<ValueType> &rect,
                                           ValueType w) {
  auto cx = rect.center().x();
  return usagi::geometry::rect<ValueType>{cx - w * static_cast<ValueType>(0.5), rect.t(),
                                          cx + w * static_cast<ValueType>(0.5), rect.b()};
}

template <usagi::utility::floating_point ValueType>
inline constexpr decltype(auto) from_height(const usagi::geometry::rect<ValueType> &rect,
                                            ValueType h) {
  auto cy = rect.center().y();
  return usagi::geometry::rect<ValueType>{rect.l(), cy - h * static_cast<ValueType>(0.5), rect.r(),
                                          cy + h * static_cast<ValueType>(0.5)};
}

template <usagi::utility::floating_point ValueType>
inline constexpr decltype(auto) from_size(const usagi::geometry::rect<ValueType> &rect, ValueType w,
                                          ValueType h) {
  auto cx = rect.center().x();
  auto cy = rect.center().y();
  return usagi::geometry::rect<ValueType>{
      cx - w * static_cast<ValueType>(0.5), cy - h * static_cast<ValueType>(0.5),
      cx + w * static_cast<ValueType>(0.5), cy + h * static_cast<ValueType>(0.5)};
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) reduce_from_left(const usagi::geometry::rect<ValueType> &rect,
                                                 ValueType l) {
  ValueType sep = rect.l() + l;
  return std::make_tuple(usagi::geometry::rect<ValueType>{sep, rect.t(), rect.r(), rect.b()},
                         usagi::geometry::rect<ValueType>{rect.l(), rect.t(), sep, rect.b()});
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) reduce_from_top(const usagi::geometry::rect<ValueType> &rect,
                                                ValueType t) {
  ValueType sep = rect.t() + t;
  return std::make_tuple(usagi::geometry::rect<ValueType>{rect.l(), sep, rect.r(), rect.b()},
                         usagi::geometry::rect<ValueType>{rect.l(), rect.t(), rect.r(), sep});
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) reduce_from_right(const usagi::geometry::rect<ValueType> &rect,
                                                  ValueType r) {
  ValueType sep = rect.r() - r;
  return std::make_tuple(usagi::geometry::rect<ValueType>{rect.l(), rect.t(), sep, rect.b()},
                         usagi::geometry::rect<ValueType>{sep, rect.t(), rect.r(), rect.b()});
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) reduce_from_bottom(const usagi::geometry::rect<ValueType> &rect,
                                                   ValueType b) {
  ValueType sep = rect.b() - b;
  return std::make_tuple(usagi::geometry::rect<ValueType>{rect.l(), rect.t(), rect.r(), sep},
                         usagi::geometry::rect<ValueType>{rect.l(), sep, rect.r(), rect.b()});
}

inline constexpr bool contain(const concepts::geometry::rect_concept auto &r,
                              const concepts::geometry::point_concept auto &p) {
  return (r.l() <= p.x() && p.x() <= r.r()) && (r.t() <= p.y() && p.y() <= r.b());
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) padding(const usagi::geometry::rect<ValueType> &rect, ValueType v) {
  constexpr usagi::utility::arithmetic auto two = static_cast<ValueType>(2);
  auto l = rect.l() + v;
  auto t = rect.t() + v;
  auto r = rect.r() - v;
  auto b = rect.b() - v;
  bool w = l < r;
  bool h = t < b;
  return usagi::geometry::rect<ValueType>{w ? l : (l + r) / two, h ? t : (t + b) / two,
                                          w ? r : (l + r) / two, h ? b : (t + b) / two};
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) padding(const usagi::geometry::rect<ValueType> &rect, ValueType tb,
                                        ValueType lr) {
  constexpr usagi::utility::arithmetic auto two = static_cast<ValueType>(2);
  auto l = rect.l() + lr;
  auto t = rect.t() + tb;
  auto r = rect.r() - lr;
  auto b = rect.b() - tb;
  bool wb = l < r;
  bool hb = t < b;
  return usagi::geometry::rect<ValueType>{wb ? l : (l + r) / two, hb ? t : (t + b) / two,
                                          wb ? r : (l + r) / two, hb ? b : (t + b) / two};
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) padding(const usagi::geometry::rect<ValueType> &rect, ValueType t,
                                        ValueType lr, ValueType b) {
  constexpr usagi::utility::arithmetic auto two = static_cast<ValueType>(2);
  auto l_ = rect.l() + lr;
  auto t_ = rect.t() + t;
  auto r_ = rect.r() - lr;
  auto b_ = rect.b() - b;
  bool wb = l_ < r_;
  bool hb = t_ < b_;
  return usagi::geometry::rect<ValueType>{wb ? l_ : (l_ + r_) / two, hb ? t_ : (t_ + b_) / two,
                                          wb ? r_ : (l_ + r_) / two, hb ? b_ : (t_ + b_) / two};
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) padding_width(const usagi::geometry::rect<ValueType> &rect,
                                              ValueType v) {
  constexpr usagi::utility::arithmetic auto two = static_cast<ValueType>(2);
  auto l = rect.l() + v;
  auto r = rect.r() - v;
  bool w = l < r;
  return usagi::geometry::rect<ValueType>{w ? l : (l + r) / two, rect.t(), w ? r : (l + r) / two,
                                          rect.b()};
}

template <usagi::utility::arithmetic ValueType>
inline constexpr decltype(auto) padding_height(const usagi::geometry::rect<ValueType> &rect,
                                               ValueType v) {
  constexpr usagi::utility::arithmetic auto two = static_cast<ValueType>(2);
  auto t = rect.t() + v;
  auto b = rect.b() - v;
  bool h = t < b;
  return usagi::geometry::rect<ValueType>{rect.l(), h ? t : (t + b) / two, rect.r(),
                                          h ? b : (t + b) / two};
}
} // namespace usagi::geometry
