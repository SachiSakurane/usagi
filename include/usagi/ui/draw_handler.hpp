#pragma once

#include <type_traits>
#include <utility>

namespace usagi::ui::detail {
/// Stores a draw callback.
///
/// @tparam FunctionType Callback type.
template <class FunctionType>
struct draw_handler {
  /// Stored callback type.
  using function_type = FunctionType;

  /// Stored callback object.
  FunctionType func;
};
} // namespace usagi::ui::detail

namespace usagi::ui {
/// Creates a draw-handler wrapper.
///
/// @param func Callback invoked with `(draw_context, offset, view)`.
/// @return Draw handler wrapping `func`.
template <class FunctionType>
inline constexpr decltype(auto) on_draw(FunctionType &&func) {
  return detail::draw_handler<std::decay_t<FunctionType>>{std::forward<FunctionType>(func)};
}
} // namespace usagi::ui
