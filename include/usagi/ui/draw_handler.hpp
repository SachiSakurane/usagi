#pragma once

#include <type_traits>
#include <utility>

namespace usagi::ui::detail {
template <class FunctionType>
struct draw_handler {
  using function_type = FunctionType;

  FunctionType func;
};
} // namespace usagi::ui::detail

namespace usagi::ui {
template <class FunctionType>
inline constexpr decltype(auto) on_draw(FunctionType &&func) {
  return detail::draw_handler<std::decay_t<FunctionType>>{std::forward<FunctionType>(func)};
}
} // namespace usagi::ui
