#pragma once

#include <type_traits>

#include <usagi/ui/draw_handler.hpp>

namespace usagi::concepts::ui {
/// Type trait used to detect UI draw handler wrappers.
///
/// @tparam Type Type to test.
template <class>
struct is_draw_handler : std::false_type {};

/// Type trait specialization for `usagi::ui::detail::draw_handler`.
///
/// @tparam FunctionType Wrapped draw callback type.
template <class FunctionType>
struct is_draw_handler<usagi::ui::detail::draw_handler<FunctionType>> : std::true_type {};

/// Convenience value for `is_draw_handler<std::remove_cvref_t<HandlerType>>::value`.
///
/// @tparam HandlerType Type to test.
template <class HandlerType>
inline constexpr bool is_draw_handler_v =
    is_draw_handler<std::remove_cvref_t<HandlerType>>::value;

/// Matches UI draw handler wrapper types.
///
/// @tparam HandlerType Type to test.
template <class HandlerType>
concept draw_handler = is_draw_handler_v<HandlerType>;
} // namespace usagi::concepts::ui
