#pragma once

#include <type_traits>
#include <utility>

namespace usagi::ui::detail {
/// Gesture event tag for down callbacks.
struct on_down_tag {};
/// Gesture event tag for drag callbacks.
struct on_drag_tag {};
/// Gesture event tag for up callbacks.
struct on_up_tag {};
/// Gesture event tag for over callbacks.
struct on_over_tag {};
/// Gesture event tag for out callbacks.
struct on_out_tag {};
/// Gesture event tag for double-click callbacks.
struct on_double_tag {};
/// Gesture event tag for wheel callbacks.
struct on_wheel_tag {};

/// Stores a gesture callback with its event tag.
///
/// @tparam Tag Gesture event tag type.
/// @tparam FunctionType Callback type.
template <class Tag, class FunctionType>
struct gesture_handler {
  /// Gesture event tag type.
  using tag_type = Tag;
  /// Stored callback type.
  using function_type = FunctionType;

  /// Stored callback object.
  FunctionType func;
};
} // namespace usagi::ui::detail

namespace usagi::ui {
/// Creates a down-event handler wrapper.
///
/// @param func Callback invoked with `(on_down, offset, view)`.
/// @return Gesture handler tagged for down events.
template <class FunctionType>
inline constexpr decltype(auto) on_down(FunctionType &&func) {
  return detail::gesture_handler<detail::on_down_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

/// Creates a drag-event handler wrapper.
///
/// @param func Callback invoked with `(on_drag, offset, view)`.
/// @return Gesture handler tagged for drag events.
template <class FunctionType>
inline constexpr decltype(auto) on_drag(FunctionType &&func) {
  return detail::gesture_handler<detail::on_drag_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

/// Creates an up-event handler wrapper.
///
/// @param func Callback invoked with `(on_up, offset, view)`.
/// @return Gesture handler tagged for up events.
template <class FunctionType>
inline constexpr decltype(auto) on_up(FunctionType &&func) {
  return detail::gesture_handler<detail::on_up_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

/// Creates an over-event handler wrapper.
///
/// @param func Callback invoked with `(on_over, offset, view)`.
/// @return Gesture handler tagged for over events.
template <class FunctionType>
inline constexpr decltype(auto) on_over(FunctionType &&func) {
  return detail::gesture_handler<detail::on_over_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

/// Creates an out-event handler wrapper.
///
/// @param func Callback invoked with `(on_out, offset, view)`.
/// @return Gesture handler tagged for out events.
template <class FunctionType>
inline constexpr decltype(auto) on_out(FunctionType &&func) {
  return detail::gesture_handler<detail::on_out_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

/// Creates a double-click-event handler wrapper.
///
/// @param func Callback invoked with `(on_double, offset, view)`.
/// @return Gesture handler tagged for double-click events.
template <class FunctionType>
inline constexpr decltype(auto) on_double(FunctionType &&func) {
  return detail::gesture_handler<detail::on_double_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

/// Creates a wheel-event handler wrapper.
///
/// @param func Callback invoked with `(on_wheel, offset, view)`.
/// @return Gesture handler tagged for wheel events.
template <class FunctionType>
inline constexpr decltype(auto) on_wheel(FunctionType &&func) {
  return detail::gesture_handler<detail::on_wheel_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

} // namespace usagi::ui
