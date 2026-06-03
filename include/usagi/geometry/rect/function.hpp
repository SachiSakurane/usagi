#pragma once

#include <algorithm>

#include <usagi/concepts/geometry.hpp>
#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/rect/rect.hpp>
#include <usagi/geometry/size/size.hpp>

namespace usagi::geometry {
/// Creates a rectangle centered on `center` with the given size.
///
/// @param center Center point of the resulting rectangle.
/// @param size Width and height of the resulting rectangle.
/// @return Rectangle centered on `center`.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) make_from_center(const usagi::geometry::point<ValueType> &center,
                                                 const usagi::geometry::size<ValueType> &size) {
  constexpr usagi::concepts::arithmetic auto two = static_cast<ValueType>(2);
  return usagi::geometry::rect<ValueType>{
      center.x() - size.width() / two, center.y() - size.height() / two,
      center.x() + size.width() / two, center.y() + size.height() / two};
}

/// Translates a rectangle by x and y offsets.
///
/// @param rect Rectangle to translate.
/// @param x Horizontal offset added to left and right edges.
/// @param y Vertical offset added to top and bottom edges.
/// @return Translated rectangle.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) translate(const usagi::geometry::rect<ValueType> &rect, ValueType x,
                                          ValueType y) {
  return usagi::geometry::rect<ValueType>{rect.l() + x, rect.t() + y, rect.r() + x, rect.b() + y};
}

/// Returns the left portion of a rectangle with the given width.
///
/// @param rect Source rectangle.
/// @param l Width measured from the source left edge.
/// @return Rectangle spanning the source left edge through `rect.l() + l`.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) from_left(const usagi::geometry::rect<ValueType> &rect,
                                          ValueType l) {
  return usagi::geometry::rect<ValueType>{rect.l(), rect.t(), rect.l() + l, rect.b()};
}

/// Returns the top portion of a rectangle with the given height.
///
/// @param rect Source rectangle.
/// @param t Height measured from the source top edge.
/// @return Rectangle spanning the source top edge through `rect.t() + t`.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) from_top(const usagi::geometry::rect<ValueType> &rect,
                                         ValueType t) {
  return usagi::geometry::rect<ValueType>{rect.l(), rect.t(), rect.r(), rect.t() + t};
}

/// Returns the right portion of a rectangle with the given width.
///
/// @param rect Source rectangle.
/// @param r Width measured backward from the source right edge.
/// @return Rectangle spanning `rect.r() - r` through the source right edge.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) from_right(const usagi::geometry::rect<ValueType> &rect,
                                           ValueType r) {
  return usagi::geometry::rect<ValueType>{rect.r() - r, rect.t(), rect.r(), rect.b()};
}

/// Returns the bottom portion of a rectangle with the given height.
///
/// @param rect Source rectangle.
/// @param b Height measured backward from the source bottom edge.
/// @return Rectangle spanning `rect.b() - b` through the source bottom edge.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) from_bottom(const usagi::geometry::rect<ValueType> &rect,
                                            ValueType b) {
  return usagi::geometry::rect<ValueType>{rect.l(), rect.b() - b, rect.r(), rect.b()};
}

/// Returns a rectangle with its width changed around the current center.
///
/// @param rect Source rectangle whose center and vertical edges are retained.
/// @param w New width.
/// @return Rectangle with width `w` centered on the source center x coordinate.
template <usagi::concepts::floating_point ValueType>
inline constexpr decltype(auto) from_width(const usagi::geometry::rect<ValueType> &rect,
                                           ValueType w) {
  auto cx = rect.center().x();
  return usagi::geometry::rect<ValueType>{cx - w * static_cast<ValueType>(0.5), rect.t(),
                                          cx + w * static_cast<ValueType>(0.5), rect.b()};
}

/// Returns a rectangle with its height changed around the current center.
///
/// @param rect Source rectangle whose center and horizontal edges are retained.
/// @param h New height.
/// @return Rectangle with height `h` centered on the source center y coordinate.
template <usagi::concepts::floating_point ValueType>
inline constexpr decltype(auto) from_height(const usagi::geometry::rect<ValueType> &rect,
                                            ValueType h) {
  auto cy = rect.center().y();
  return usagi::geometry::rect<ValueType>{rect.l(), cy - h * static_cast<ValueType>(0.5), rect.r(),
                                          cy + h * static_cast<ValueType>(0.5)};
}

/// Returns a rectangle with its size changed around the current center.
///
/// @param rect Source rectangle whose center is retained.
/// @param w New width.
/// @param h New height.
/// @return Rectangle with size `(w, h)` centered on the source center.
template <usagi::concepts::floating_point ValueType>
inline constexpr decltype(auto) from_size(const usagi::geometry::rect<ValueType> &rect, ValueType w,
                                          ValueType h) {
  auto cx = rect.center().x();
  auto cy = rect.center().y();
  return usagi::geometry::rect<ValueType>{
      cx - w * static_cast<ValueType>(0.5), cy - h * static_cast<ValueType>(0.5),
      cx + w * static_cast<ValueType>(0.5), cy + h * static_cast<ValueType>(0.5)};
}

/// Splits off the left portion and returns `(left_part, remainder)`.
///
/// @param rect Source rectangle.
/// @param l Width of the portion split from the left edge.
/// @return Tuple containing the left portion followed by the remaining rectangle.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) reduce_from_left(const usagi::geometry::rect<ValueType> &rect,
                                                 ValueType l) {
  ValueType sep = rect.l() + l;
  return std::make_tuple(usagi::geometry::rect<ValueType>{rect.l(), rect.t(), sep, rect.b()},
                         usagi::geometry::rect<ValueType>{sep, rect.t(), rect.r(), rect.b()});
}

/// Splits off the top portion and returns `(top_part, remainder)`.
///
/// @param rect Source rectangle.
/// @param t Height of the portion split from the top edge.
/// @return Tuple containing the top portion followed by the remaining rectangle.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) reduce_from_top(const usagi::geometry::rect<ValueType> &rect,
                                                ValueType t) {
  ValueType sep = rect.t() + t;
  return std::make_tuple(usagi::geometry::rect<ValueType>{rect.l(), rect.t(), rect.r(), sep},
                         usagi::geometry::rect<ValueType>{rect.l(), sep, rect.r(), rect.b()});
}

/// Splits off the right portion and returns `(right_part, remainder)`.
///
/// @param rect Source rectangle.
/// @param r Width of the portion split from the right edge.
/// @return Tuple containing the right portion followed by the remaining rectangle.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) reduce_from_right(const usagi::geometry::rect<ValueType> &rect,
                                                  ValueType r) {
  ValueType sep = rect.r() - r;
  return std::make_tuple(usagi::geometry::rect<ValueType>{sep, rect.t(), rect.r(), rect.b()},
                         usagi::geometry::rect<ValueType>{rect.l(), rect.t(), sep, rect.b()});
}

/// Splits off the bottom portion and returns `(bottom_part, remainder)`.
///
/// @param rect Source rectangle.
/// @param b Height of the portion split from the bottom edge.
/// @return Tuple containing the bottom portion followed by the remaining rectangle.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) reduce_from_bottom(const usagi::geometry::rect<ValueType> &rect,
                                                   ValueType b) {
  ValueType sep = rect.b() - b;
  return std::make_tuple(usagi::geometry::rect<ValueType>{rect.l(), sep, rect.r(), rect.b()},
                         usagi::geometry::rect<ValueType>{rect.l(), rect.t(), rect.r(), sep});
}

/// Returns whether `p` is inside `r`, including edges.
///
/// @param r Rectangle-like area to test against.
/// @param p Point-like coordinate to test.
/// @return `true` when `p` is inside or on the edges of `r`; otherwise `false`.
inline constexpr bool contain(const concepts::geometry::rect_concept auto &r,
                              const concepts::geometry::point_concept auto &p) {
  return (r.l() <= p.x() && p.x() <= r.r()) && (r.t() <= p.y() && p.y() <= r.b());
}

/// Returns a rectangle inset by the same amount on all sides.
///
/// @param rect Source rectangle.
/// @param v Inset applied to left, top, right, and bottom edges.
/// @return Padded rectangle, clamped to the center when the inset crosses an axis.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) padding(const usagi::geometry::rect<ValueType> &rect, ValueType v) {
  constexpr usagi::concepts::arithmetic auto two = static_cast<ValueType>(2);
  auto l = rect.l() + v;
  auto t = rect.t() + v;
  auto r = rect.r() - v;
  auto b = rect.b() - v;
  bool w = l < r;
  bool h = t < b;
  return usagi::geometry::rect<ValueType>{w ? l : (l + r) / two, h ? t : (t + b) / two,
                                          w ? r : (l + r) / two, h ? b : (t + b) / two};
}

/// Returns a rectangle inset by vertical and horizontal amounts.
///
/// @param rect Source rectangle.
/// @param tb Inset applied to top and bottom edges.
/// @param lr Inset applied to left and right edges.
/// @return Padded rectangle, clamped to the center when an inset crosses an axis.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) padding(const usagi::geometry::rect<ValueType> &rect, ValueType tb,
                                        ValueType lr) {
  constexpr usagi::concepts::arithmetic auto two = static_cast<ValueType>(2);
  auto l = rect.l() + lr;
  auto t = rect.t() + tb;
  auto r = rect.r() - lr;
  auto b = rect.b() - tb;
  bool wb = l < r;
  bool hb = t < b;
  return usagi::geometry::rect<ValueType>{wb ? l : (l + r) / two, hb ? t : (t + b) / two,
                                          wb ? r : (l + r) / two, hb ? b : (t + b) / two};
}

/// Returns a rectangle inset by top, horizontal, and bottom amounts.
///
/// @param rect Source rectangle.
/// @param t Inset applied to the top edge.
/// @param lr Inset applied to left and right edges.
/// @param b Inset applied to the bottom edge.
/// @return Padded rectangle, clamped to the center when an inset crosses an axis.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) padding(const usagi::geometry::rect<ValueType> &rect, ValueType t,
                                        ValueType lr, ValueType b) {
  constexpr usagi::concepts::arithmetic auto two = static_cast<ValueType>(2);
  auto l_ = rect.l() + lr;
  auto t_ = rect.t() + t;
  auto r_ = rect.r() - lr;
  auto b_ = rect.b() - b;
  bool wb = l_ < r_;
  bool hb = t_ < b_;
  return usagi::geometry::rect<ValueType>{wb ? l_ : (l_ + r_) / two, hb ? t_ : (t_ + b_) / two,
                                          wb ? r_ : (l_ + r_) / two, hb ? b_ : (t_ + b_) / two};
}

/// Returns a rectangle inset on the left and right sides.
///
/// @param rect Source rectangle.
/// @param v Inset applied to left and right edges.
/// @return Padded rectangle with vertical edges unchanged.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) padding_width(const usagi::geometry::rect<ValueType> &rect,
                                              ValueType v) {
  constexpr usagi::concepts::arithmetic auto two = static_cast<ValueType>(2);
  auto l = rect.l() + v;
  auto r = rect.r() - v;
  bool w = l < r;
  return usagi::geometry::rect<ValueType>{w ? l : (l + r) / two, rect.t(), w ? r : (l + r) / two,
                                          rect.b()};
}

/// Returns a rectangle inset on the top and bottom sides.
///
/// @param rect Source rectangle.
/// @param v Inset applied to top and bottom edges.
/// @return Padded rectangle with horizontal edges unchanged.
template <usagi::concepts::arithmetic ValueType>
inline constexpr decltype(auto) padding_height(const usagi::geometry::rect<ValueType> &rect,
                                               ValueType v) {
  constexpr usagi::concepts::arithmetic auto two = static_cast<ValueType>(2);
  auto t = rect.t() + v;
  auto b = rect.b() - v;
  bool h = t < b;
  return usagi::geometry::rect<ValueType>{rect.l(), h ? t : (t + b) / two, rect.r(),
                                          h ? b : (t + b) / two};
}
} // namespace usagi::geometry
