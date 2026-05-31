#pragma once

#include <type_traits>

#include <usagi/ui/draw_handler.hpp>

namespace usagi::concepts::ui {
template <class>
struct is_draw_handler : std::false_type {};

template <class FunctionType>
struct is_draw_handler<usagi::ui::detail::draw_handler<FunctionType>> : std::true_type {};

template <class HandlerType>
inline constexpr bool is_draw_handler_v =
    is_draw_handler<std::remove_cvref_t<HandlerType>>::value;

template <class HandlerType>
concept draw_handler = is_draw_handler_v<HandlerType>;
} // namespace usagi::concepts::ui
