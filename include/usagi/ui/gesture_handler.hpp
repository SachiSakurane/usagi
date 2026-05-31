#pragma once

#include <type_traits>
#include <utility>

namespace usagi::ui::detail {
struct on_down_tag {};
struct on_drag_tag {};
struct on_up_tag {};
struct on_over_tag {};
struct on_out_tag {};
struct on_double_tag {};
struct on_wheel_tag {};

template <class Tag, class FunctionType>
struct gesture_handler {
  using tag_type = Tag;
  using function_type = FunctionType;

  FunctionType func;
};
} // namespace usagi::ui::detail

namespace usagi::ui {
template <class FunctionType>
inline constexpr decltype(auto) on_down(FunctionType &&func) {
  return detail::gesture_handler<detail::on_down_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

template <class FunctionType>
inline constexpr decltype(auto) on_drag(FunctionType &&func) {
  return detail::gesture_handler<detail::on_drag_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

template <class FunctionType>
inline constexpr decltype(auto) on_up(FunctionType &&func) {
  return detail::gesture_handler<detail::on_up_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

template <class FunctionType>
inline constexpr decltype(auto) on_over(FunctionType &&func) {
  return detail::gesture_handler<detail::on_over_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

template <class FunctionType>
inline constexpr decltype(auto) on_out(FunctionType &&func) {
  return detail::gesture_handler<detail::on_out_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

template <class FunctionType>
inline constexpr decltype(auto) on_double(FunctionType &&func) {
  return detail::gesture_handler<detail::on_double_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

template <class FunctionType>
inline constexpr decltype(auto) on_wheel(FunctionType &&func) {
  return detail::gesture_handler<detail::on_wheel_tag, std::decay_t<FunctionType>>{
      std::forward<FunctionType>(func)};
}

} // namespace usagi::ui
