#pragma once

#include <concepts>
#include <tuple>
#include <type_traits>
#include <utility>

#include <usagi/concepts/ui/viewable.hpp>

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

template <class>
struct is_gesture_handler : std::false_type {};

template <class Tag, class FunctionType>
struct is_gesture_handler<gesture_handler<Tag, FunctionType>> : std::true_type {};

template <class HandlerType>
inline constexpr bool is_gesture_handler_v =
    is_gesture_handler<std::remove_cvref_t<HandlerType>>::value;

template <class HandlerType, class Tag>
concept gesture_handler_for =
    is_gesture_handler_v<HandlerType> &&
    std::same_as<typename std::remove_cvref_t<HandlerType>::tag_type, Tag>;

template <class HandlerType, class Tag, class ReturnType, class... Args>
consteval bool tagged_gesture_func_requirement_impl() {
  if constexpr (!gesture_handler_for<HandlerType, Tag>) {
    return false;
  } else {
    return std::is_invocable_r_v<ReturnType,
                                 typename std::remove_cvref_t<HandlerType>::function_type, Args...>;
  }
}

template <usagi::concepts::ui::viewable ViewType, class HandlerType>
consteval bool gesture_handler_requirement_impl() {
  using gesture_traits =
      typename usagi::type::gesture_traits<typename ViewType::gesture_parameter_type>;
  return tagged_gesture_func_requirement_impl<HandlerType, on_down_tag, bool,
                                              typename gesture_traits::on_down_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, on_drag_tag, void,
                                              typename gesture_traits::on_drag_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, on_up_tag, void,
                                              typename gesture_traits::on_up_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, on_over_tag, bool,
                                              typename gesture_traits::on_over_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, on_out_tag, void,
                                              typename gesture_traits::on_out_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, on_double_tag, bool,
                                              typename gesture_traits::on_double_type,
                                              typename gesture_traits::offset_type, ViewType &>() ||
         tagged_gesture_func_requirement_impl<HandlerType, on_wheel_tag, bool,
                                              typename gesture_traits::on_wheel_type,
                                              typename gesture_traits::offset_type, ViewType &>();
}

template <usagi::concepts::ui::viewable ViewType>
consteval bool gesture_handler_requirement() {
  return true;
}

template <usagi::concepts::ui::viewable ViewType, class Front, class... HandlerTypes>
consteval bool gesture_handler_requirement() {
  return gesture_handler_requirement_impl<ViewType, Front>() &&
         gesture_handler_requirement<ViewType, HandlerTypes...>();
}

template <class TupleType, usagi::concepts::ui::viewable ViewType, std::size_t... Sequence>
consteval bool apply_tuple_requirement(std::index_sequence<Sequence...>) {
  return gesture_handler_requirement<ViewType, std::tuple_element_t<Sequence, TupleType>...>();
}

template <class TupleType, class ViewType>
concept gesture_tuple_requirement = usagi::concepts::ui::viewable<ViewType> &&
                                    apply_tuple_requirement<TupleType, ViewType>(
                                        std::make_index_sequence<std::tuple_size_v<TupleType>>());
} // namespace usagi::ui::detail
