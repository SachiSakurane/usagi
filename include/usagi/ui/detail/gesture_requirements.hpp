#pragma once

#include <tuple>
#include <utility>

#include <usagi/concepts/ui/viewable.hpp>

namespace usagi::ui::detail {
template <usagi::concepts::ui::viewable ViewType, class FunctionType>
consteval bool gesture_func_requirement_impl() {
  using gesture_traits =
      typename usagi::type::gesture_traits<typename ViewType::gesture_parameter_type>;
  return std::is_invocable_r_v<bool, FunctionType, typename gesture_traits::on_down_type,
                               ViewType &> ||
         std::is_invocable_r_v<void, FunctionType, typename gesture_traits::on_drag_type,
                               ViewType &> ||
         std::is_invocable_r_v<void, FunctionType, typename gesture_traits::on_up_type,
                               ViewType &> ||
         std::is_invocable_r_v<bool, FunctionType, typename gesture_traits::on_over_type,
                               ViewType &> ||
         std::is_invocable_r_v<void, FunctionType, typename gesture_traits::on_out_type,
                               ViewType &> ||
         std::is_invocable_r_v<bool, FunctionType, typename gesture_traits::on_double_type,
                               ViewType &> ||
         std::is_invocable_r_v<bool, FunctionType, typename gesture_traits::on_wheel_type,
                               ViewType &>;
}

template <usagi::concepts::ui::viewable ViewType>
consteval bool gesture_func_requirement() {
  return true;
}

template <usagi::concepts::ui::viewable ViewType, class Front, class... FunctionTypes>
consteval bool gesture_func_requirement() {
  return gesture_func_requirement_impl<ViewType, Front>() &&
         gesture_func_requirement<ViewType, FunctionTypes...>();
}

template <class TupleType, usagi::concepts::ui::viewable ViewType, std::size_t... Sequence>
consteval bool apply_tuple_requirement(std::index_sequence<Sequence...>) {
  return gesture_func_requirement<ViewType, std::tuple_element_t<Sequence, TupleType>...>();
}

template <class TupleType, class ViewType>
concept gesture_tuple_requirement = usagi::concepts::ui::viewable<ViewType> &&
    apply_tuple_requirement<TupleType, ViewType>(
        std::make_index_sequence<std::tuple_size_v<TupleType>>());
} // namespace usagi::ui::detail
