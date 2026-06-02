#pragma once

#include <concepts>
#include <tuple>
#include <type_traits>
#include <utility>

#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/ui/gesture_handler.hpp>

namespace usagi::concepts::ui {
/// Type trait used to detect UI gesture handler wrappers.
///
/// @tparam Type Type to test.
template <class>
struct is_gesture_handler : std::false_type {};

/// Type trait specialization for `usagi::ui::detail::gesture_handler`.
///
/// @tparam Tag Gesture event tag type.
/// @tparam FunctionType Wrapped gesture callback type.
template <class Tag, class FunctionType>
struct is_gesture_handler<usagi::ui::detail::gesture_handler<Tag, FunctionType>> : std::true_type {
};

/// Convenience value for `is_gesture_handler<std::remove_cvref_t<HandlerType>>::value`.
///
/// @tparam HandlerType Type to test.
template <class HandlerType>
inline constexpr bool is_gesture_handler_v =
    is_gesture_handler<std::remove_cvref_t<HandlerType>>::value;

namespace detail {
/// Matches gesture handlers for a specific gesture event tag.
///
/// @tparam HandlerType Handler wrapper type to test.
/// @tparam Tag Required gesture event tag.
template <class HandlerType, class Tag>
concept gesture_handler_for =
    is_gesture_handler_v<HandlerType> &&
    std::same_as<typename std::remove_cvref_t<HandlerType>::tag_type, Tag>;

/// Checks whether a tagged gesture handler can be invoked with the required signature.
///
/// @tparam HandlerType Handler wrapper type to test.
/// @tparam Tag Required gesture event tag.
/// @tparam ReturnType Required callback return type.
/// @tparam Args Required callback argument types.
/// @return `true` when the handler tag and callback signature match.
template <class HandlerType, class Tag, class ReturnType, class... Args>
consteval bool tagged_gesture_func_requirement_impl() {
  if constexpr (!gesture_handler_for<HandlerType, Tag>) {
    return false;
  } else {
    return std::is_invocable_r_v<ReturnType,
                                 typename std::remove_cvref_t<HandlerType>::function_type, Args...>;
  }
}

/// Checks whether one handler is valid for any gesture event of `ViewType`.
///
/// @tparam ViewType View type that receives the gesture.
/// @tparam HandlerType Handler wrapper type to test.
/// @return `true` when the handler matches one supported gesture callback signature.
template <usagi::concepts::ui::viewable ViewType, class HandlerType>
consteval bool gesture_handler_requirement_impl() {
  using gesture_traits =
      typename usagi::type::gesture_traits<typename ViewType::gesture_parameter_type>;
  return tagged_gesture_func_requirement_impl<HandlerType, usagi::ui::detail::on_down_tag, bool,
                                              typename gesture_traits::on_down_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, usagi::ui::detail::on_drag_tag, void,
                                              typename gesture_traits::on_drag_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, usagi::ui::detail::on_up_tag, void,
                                              typename gesture_traits::on_up_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, usagi::ui::detail::on_over_tag, bool,
                                              typename gesture_traits::on_over_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, usagi::ui::detail::on_out_tag, void,
                                              typename gesture_traits::on_out_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, usagi::ui::detail::on_double_tag, bool,
                                              typename gesture_traits::on_double_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, usagi::ui::detail::on_wheel_tag, bool,
                                              typename gesture_traits::on_wheel_type,
                                              typename gesture_traits::offset_type, ViewType &>();
}

/// Base case for validating zero gesture handlers.
///
/// @tparam ViewType View type that receives the gesture.
/// @return Always `true`.
template <usagi::concepts::ui::viewable ViewType>
consteval bool gesture_handler_requirement() {
  return true;
}

/// Checks whether all handler types are valid for `ViewType`.
///
/// @tparam ViewType View type that receives the gestures.
/// @tparam Front First handler wrapper type to test.
/// @tparam HandlerTypes Remaining handler wrapper types to test.
/// @return `true` when every handler is valid for the view.
template <usagi::concepts::ui::viewable ViewType, class Front, class... HandlerTypes>
consteval bool gesture_handler_requirement() {
  return gesture_handler_requirement_impl<ViewType, Front>() &&
         gesture_handler_requirement<ViewType, HandlerTypes...>();
}

/// Applies gesture handler validation to each element in a tuple.
///
/// @tparam TupleType Tuple of handler wrapper types.
/// @tparam ViewType View type that receives the gestures.
/// @tparam Sequence Tuple element indexes.
/// @return `true` when all tuple elements are valid gesture handlers for `ViewType`.
template <class TupleType, usagi::concepts::ui::viewable ViewType, std::size_t... Sequence>
consteval bool apply_tuple_requirement(std::index_sequence<Sequence...>) {
  return gesture_handler_requirement<ViewType, std::tuple_element_t<Sequence, TupleType>...>();
}
} // namespace detail

/// Matches tuples whose handler elements are valid for a view type.
///
/// @tparam TupleType Tuple of handler wrapper types.
/// @tparam ViewType View type that receives the gestures.
template <class TupleType, class ViewType>
concept gesture_tuple_requirement = usagi::concepts::ui::viewable<ViewType> &&
                                    detail::apply_tuple_requirement<TupleType, ViewType>(
                                        std::make_index_sequence<std::tuple_size_v<TupleType>>());
} // namespace usagi::concepts::ui
