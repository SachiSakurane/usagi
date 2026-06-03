#pragma once

#include <tuple>
#include <utility>

#include <usagi/concepts/ui/gesture_handler.hpp>
#include <usagi/concepts/ui/transformable.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/ui/gesture_handler.hpp>

namespace usagi::ui {
namespace detail {
  /// Invokes a matching consumable gesture handler.
  ///
  /// @tparam Tag Gesture event tag to match.
  /// @tparam HandlerType Handler wrapper type.
  /// @tparam Args Callback argument types.
  /// @param handler Handler wrapper to inspect and invoke.
  /// @param args Arguments forwarded to the callback.
  /// @return Callback result when the tag matches; otherwise `false`.
  template <class Tag, class HandlerType, class... Args>
  constexpr bool invoke_consumable_handler(HandlerType &handler, Args &&...args) {
    if constexpr (usagi::concepts::ui::detail::gesture_handler_for<HandlerType, Tag>) {
      return handler.func(std::forward<Args>(args)...);
    } else {
      return false;
    }
  }

  /// Invokes a matching non-consuming gesture handler.
  ///
  /// @tparam Tag Gesture event tag to match.
  /// @tparam HandlerType Handler wrapper type.
  /// @tparam Args Callback argument types.
  /// @param handler Handler wrapper to inspect and invoke.
  /// @param args Arguments forwarded to the callback.
  template <class Tag, class HandlerType, class... Args>
  constexpr void invoke_nonconsumable_handler(HandlerType &handler, Args &&...args) {
    if constexpr (usagi::concepts::ui::detail::gesture_handler_for<HandlerType, Tag>) {
      handler.func(std::forward<Args>(args)...);
    }
  }

  /// Invokes all matching consumable gesture handlers in a tuple.
  ///
  /// @tparam Tag Gesture event tag to match.
  /// @tparam TupleType Tuple of handler wrappers.
  /// @tparam Args Callback argument types.
  /// @param handlers Handler tuple.
  /// @param args Arguments forwarded to each matching callback.
  /// @return `true` when any matching handler consumes the event.
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

  /// Invokes all matching non-consuming gesture handlers in a tuple.
  ///
  /// @tparam Tag Gesture event tag to match.
  /// @tparam TupleType Tuple of handler wrappers.
  /// @tparam Args Callback argument types.
  /// @param handlers Handler tuple.
  /// @param args Arguments forwarded to each matching callback.
  template <class Tag, class TupleType, class... Args>
  constexpr void invoke_nonconsumable_handlers(TupleType &handlers, Args &&...args) {
    std::apply(
        [&](auto &...handler) {
          (invoke_nonconsumable_handler<Tag>(handler, std::forward<Args>(args)...), ...);
        },
        handlers);
  }

  /// Pipe payload used to attach gesture handlers to a view.
  ///
  /// @tparam TupleType Tuple of gesture handler wrappers.
  template <class TupleType>
  struct gesture_holder {
    /// Stored gesture handler tuple.
    TupleType elem;
  };

  template <class TupleType>
  gesture_holder(TupleType &&) -> gesture_holder<TupleType>;
} // namespace detail

/// View decorator that invokes gesture handlers before forwarding to the wrapped view.
///
/// @tparam ViewType Wrapped viewable type.
/// @tparam TupleType Tuple of gesture handler wrappers.
template <usagi::concepts::ui::viewable ViewType, class TupleType>
requires usagi::concepts::ui::transformable<ViewType>
struct gesture {
  /// Shared geometry value type.
  using value_type = typename ViewType::value_type;
  /// Point type using `value_type`.
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  /// Rectangle type using `value_type`.
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  /// Size type using `value_type`.
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  /// Transform type using `value_type`.
  using transform_type = typename usagi::geometry::geometry_traits<value_type>::transform_type;
  /// Mutable drawing context type.
  using draw_context_type = typename ViewType::draw_context_type;
  /// Draw and event offset type.
  using offset_type = typename ViewType::offset_type;
  /// Raw gesture parameter payload type.
  using gesture_parameter_type = typename ViewType::gesture_parameter_type;
  /// Gesture event type bundle.
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  /// Creates a gesture decorator.
  ///
  /// @param v View to decorate.
  /// @param t Tuple of gesture handler wrappers.
  constexpr gesture(ViewType &&v, TupleType &&t)
      : holder{std::move(v)}, handlers{std::forward<TupleType>(t)} {}

  /// Draws the wrapped view.
  ///
  /// @param context Mutable drawing context.
  /// @param offset Accumulated offset from the root view.
  void draw(draw_context_type &context, offset_type offset) { holder.draw(context, offset); }

  /// Returns the wrapped view bounds.
  ///
  /// @return Bounds reported by the wrapped view.
  size_type bounds() const { return holder.bounds(); }
  /// Returns the wrapped view frame.
  ///
  /// @return Frame reported by the wrapped view.
  rect_type frame() const { return holder.frame(); }

  /// Runs down handlers, then forwards when no handler consumes the event.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when a handler or the wrapped view consumes the event.
  bool event(typename gesture_traits::on_down_type parameter, offset_type offset) {
    if (detail::invoke_consumable_handlers<detail::on_down_tag>(handlers, parameter, offset,
                                                                holder)) {
      return true;
    }
    return holder.event(parameter, offset);
  }

  /// Runs drag handlers, then forwards the event.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  void event(typename gesture_traits::on_drag_type parameter, offset_type offset) {
    detail::invoke_nonconsumable_handlers<detail::on_drag_tag>(handlers, parameter, offset,
                                                               holder);
    holder.event(parameter, offset);
  }

  /// Runs up handlers, then forwards the event.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  void event(typename gesture_traits::on_up_type parameter, offset_type offset) {
    detail::invoke_nonconsumable_handlers<detail::on_up_tag>(handlers, parameter, offset, holder);
    holder.event(parameter, offset);
  }

  /// Runs over handlers, then forwards when no handler consumes the event.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when a handler or the wrapped view consumes the event.
  bool event(typename gesture_traits::on_over_type parameter, offset_type offset) {
    if (detail::invoke_consumable_handlers<detail::on_over_tag>(handlers, parameter, offset,
                                                                holder)) {
      return true;
    }
    return holder.event(parameter, offset);
  }

  /// Runs out handlers, then forwards the event.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  void event(typename gesture_traits::on_out_type parameter, offset_type offset) {
    detail::invoke_nonconsumable_handlers<detail::on_out_tag>(handlers, parameter, offset,
                                                              holder);
    holder.event(parameter, offset);
  }

  /// Runs double-click handlers, then forwards when no handler consumes the event.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when a handler or the wrapped view consumes the event.
  bool event(typename gesture_traits::on_double_type parameter, offset_type offset) {
    if (detail::invoke_consumable_handlers<detail::on_double_tag>(handlers, parameter, offset,
                                                                  holder)) {
      return true;
    }
    return holder.event(parameter, offset);
  }

  /// Runs wheel handlers, then forwards when no handler consumes the event.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when a handler or the wrapped view consumes the event.
  bool event(typename gesture_traits::on_wheel_type parameter, offset_type offset) {
    if (detail::invoke_consumable_handlers<detail::on_wheel_tag>(handlers, parameter, offset,
                                                                 holder)) {
      return true;
    }
    return holder.event(parameter, offset);
  }

  /// Updates the wrapped view's active press state.
  ///
  /// @param flag New press-state value.
  void set_down(bool flag) { holder.set_down(flag); }
  /// Updates the wrapped view's pointer-over state.
  ///
  /// @param flag New over-state value.
  void set_over(bool flag) { holder.set_over(flag); }
  /// Returns whether the wrapped view is currently pressed.
  ///
  /// @return Current press-state value.
  [[nodiscard]] bool is_downed() const { return holder.is_downed(); }
  /// Returns whether the pointer is currently over the wrapped view.
  ///
  /// @return Current over-state value.
  [[nodiscard]] bool is_overed() const { return holder.is_overed(); }

  /// Updates whether the wrapped view participates in draw and event traversal.
  ///
  /// @param flag New enabled-state value.
  void set_enabled(bool flag) { holder.set_enabled(flag); }
  /// Returns whether the wrapped view is enabled.
  ///
  /// @return Current enabled-state value.
  [[nodiscard]] bool is_enabled() const { return holder.is_enabled(); }

  /// Returns the wrapped view's layout-after transform.
  ///
  /// @return Transform reported by the wrapped view.
  [[nodiscard]] constexpr transform_type transform() const { return holder.transform(); }
  /// Replaces the wrapped view's layout-after transform.
  ///
  /// @param t New transform value.
  constexpr void set_transform(transform_type t) { holder.set_transform(t); }

  /// Returns the wrapped view's transform translation.
  ///
  /// @return Translation applied after frame placement.
  [[nodiscard]] constexpr point_type translation() const { return holder.translation(); }
  /// Updates the wrapped view's transform translation.
  ///
  /// @param p New translation value.
  constexpr void set_translation(point_type p) { holder.set_translation(p); }

  /// Returns the wrapped view's transform rotation.
  ///
  /// @return Current rotation angle in radians.
  [[nodiscard]] constexpr value_type rotation() const { return holder.rotation(); }
  /// Updates the wrapped view's transform rotation without changing the current origin.
  ///
  /// @param r New rotation angle in radians.
  constexpr void set_rotation(value_type r) { holder.set_rotation(r); }

  /// Returns the wrapped view's transform scale.
  ///
  /// @return Current x and y scale factors.
  [[nodiscard]] constexpr point_type scale() const { return holder.scale(); }
  /// Updates the wrapped view's transform scale without changing the current origin.
  ///
  /// @param s New x and y scale factors.
  constexpr void set_scale(point_type s) { holder.set_scale(s); }
  /// Updates the wrapped view's transform scale and transform origin together.
  ///
  /// @param s New x and y scale factors.
  /// @param origin Origin used by the scale operation.
  constexpr void set_scale(point_type s, point_type origin) { holder.set_scale(s, origin); }

private:
  ViewType holder;
  TupleType handlers;
};

/// Attaches gesture handlers to a view with the pipe operator.
///
/// @param v View to decorate.
/// @param wrapped Gesture handler tuple holder.
/// @return Gesture-decorated view.
template <usagi::concepts::ui::viewable ViewType,
          usagi::concepts::ui::gesture_tuple_requirement<ViewType> TupleType>
requires usagi::concepts::ui::transformable<ViewType>
inline constexpr decltype(auto) operator|(ViewType &&v,
                                          detail::gesture_holder<TupleType> &&wrapped) {
  return gesture<ViewType, TupleType>{std::forward<ViewType>(v),
                                      std::forward<detail::gesture_holder<TupleType>>(wrapped)
                                          .elem};
}

/// Creates a pipe payload containing gesture handlers.
///
/// @param funcs Gesture handler wrappers created by `on_down`, `on_drag`, and related helpers.
/// @return Gesture holder that can be piped into a view.
template <class... FunctionTypes>
inline constexpr decltype(auto) gestured(FunctionTypes &&...funcs) {
  return detail::gesture_holder{std::make_tuple(std::forward<FunctionTypes>(funcs)...)};
}
} // namespace usagi::ui
