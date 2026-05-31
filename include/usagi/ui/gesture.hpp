#pragma once

#include <tuple>
#include <utility>

#include <usagi/concepts/ui/gesture_handler.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/ui/gesture_handler.hpp>

namespace usagi::ui {
namespace detail {
  template <class Tag, class HandlerType, class... Args>
  constexpr bool invoke_consumable_handler(HandlerType &handler, Args &&...args) {
    if constexpr (usagi::concepts::ui::gesture_handler_for<HandlerType, Tag>) {
      return handler.func(std::forward<Args>(args)...);
    } else {
      return false;
    }
  }

  template <class Tag, class HandlerType, class... Args>
  constexpr void invoke_nonconsumable_handler(HandlerType &handler, Args &&...args) {
    if constexpr (usagi::concepts::ui::gesture_handler_for<HandlerType, Tag>) {
      handler.func(std::forward<Args>(args)...);
    }
  }

  template <class Tag, class TupleType, class... Args>
  constexpr bool invoke_consumable_handlers(TupleType &handlers, Args &&...args) {
    auto consumed = false;
    std::apply(
        [&](auto &...handler) {
          ((consumed = consumed || invoke_consumable_handler<Tag>(
                                      handler, std::forward<Args>(args)...)),
           ...);
        },
        handlers);
    return consumed;
  }

  template <class Tag, class TupleType, class... Args>
  constexpr void invoke_nonconsumable_handlers(TupleType &handlers, Args &&...args) {
    std::apply(
        [&](auto &...handler) {
          (invoke_nonconsumable_handler<Tag>(handler, std::forward<Args>(args)...), ...);
        },
        handlers);
  }
} // namespace detail

template <class TupleType>
struct gesture_holder {
  TupleType elem;
};

template <class TupleType>
gesture_holder(TupleType &&) -> gesture_holder<TupleType>;

template <usagi::concepts::ui::viewable ViewType, class TupleType>
struct gesture {
  using value_type = typename ViewType::value_type;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = typename ViewType::draw_context_type;
  using offset_type = typename ViewType::offset_type;
  using gesture_parameter_type = typename ViewType::gesture_parameter_type;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  gesture(ViewType &&v, TupleType &&t)
      : holder{std::move(v)}, handlers{std::forward<TupleType>(t)} {}

  void draw(draw_context_type &context, offset_type offset) { holder.draw(context, offset); }

  size_type bounds() const { return holder.bounds(); }
  rect_type frame() const { return holder.frame(); }

  bool event(typename gesture_traits::on_down_type parameter, offset_type offset) {
    if (detail::invoke_consumable_handlers<detail::on_down_tag>(handlers, parameter, offset,
                                                                holder)) {
      return true;
    }
    return holder.event(parameter, offset);
  }

  void event(typename gesture_traits::on_drag_type parameter, offset_type offset) {
    detail::invoke_nonconsumable_handlers<detail::on_drag_tag>(handlers, parameter, offset,
                                                               holder);
    holder.event(parameter, offset);
  }

  void event(typename gesture_traits::on_up_type parameter, offset_type offset) {
    detail::invoke_nonconsumable_handlers<detail::on_up_tag>(handlers, parameter, offset, holder);
    holder.event(parameter, offset);
  }

  bool event(typename gesture_traits::on_over_type parameter, offset_type offset) {
    if (detail::invoke_consumable_handlers<detail::on_over_tag>(handlers, parameter, offset,
                                                                holder)) {
      return true;
    }
    return holder.event(parameter, offset);
  }

  void event(typename gesture_traits::on_out_type parameter, offset_type offset) {
    detail::invoke_nonconsumable_handlers<detail::on_out_tag>(handlers, parameter, offset,
                                                              holder);
    holder.event(parameter, offset);
  }

  bool event(typename gesture_traits::on_double_type parameter, offset_type offset) {
    if (detail::invoke_consumable_handlers<detail::on_double_tag>(handlers, parameter, offset,
                                                                  holder)) {
      return true;
    }
    return holder.event(parameter, offset);
  }

  bool event(typename gesture_traits::on_wheel_type parameter, offset_type offset) {
    if (detail::invoke_consumable_handlers<detail::on_wheel_tag>(handlers, parameter, offset,
                                                                 holder)) {
      return true;
    }
    return holder.event(parameter, offset);
  }

  void set_down(bool flag) { holder.set_down(flag); }
  void set_over(bool flag) { holder.set_over(flag); }
  [[nodiscard]] bool is_downed() const { return holder.is_downed(); }
  [[nodiscard]] bool is_overed() const { return holder.is_overed(); }

  void set_enabled(bool flag) { holder.set_enabled(flag); }
  [[nodiscard]] bool is_enabled() const { return holder.is_enabled(); }

private:
  ViewType holder;
  TupleType handlers;
};

template <usagi::concepts::ui::viewable ViewType,
          usagi::concepts::ui::gesture_tuple_requirement<ViewType> TupleType>
inline constexpr decltype(auto) operator|(ViewType &&v, gesture_holder<TupleType> &&wrapped) {
  return gesture<ViewType, TupleType>{std::forward<ViewType>(v),
                                      std::forward<gesture_holder<TupleType>>(wrapped).elem};
}

template <class... FunctionTypes>
inline constexpr decltype(auto) gestured(FunctionTypes &&...funcs) {
  return gesture_holder{std::make_tuple(std::forward<FunctionTypes>(funcs)...)};
}
} // namespace usagi::ui
