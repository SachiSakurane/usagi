#pragma once

#include <type_traits>
#include <utility>

#include <usagi/concepts/invocable.hpp>
#include <usagi/concepts/ui/draw_handler.hpp>
#include <usagi/concepts/ui/transformable.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/ui/draw_handler.hpp>

namespace usagi::ui {
/// View decorator that runs a draw handler before drawing the wrapped view.
///
/// @tparam ViewType Wrapped viewable type.
/// @tparam HandlerType Draw handler wrapper type.
template <usagi::concepts::ui::viewable ViewType, usagi::concepts::ui::draw_handler HandlerType>
requires usagi::concepts::ui::transformable<ViewType> &&
    usagi::concepts::invocable<typename HandlerType::function_type,
                               typename ViewType::draw_context_type &,
                               typename ViewType::offset_type, const ViewType &>
struct surface {
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

  /// Creates a draw-decorated view.
  ///
  /// @param v View to decorate.
  /// @param handler Draw handler invoked before the wrapped view draws.
  constexpr surface(ViewType &&v, HandlerType handler)
      : holder{std::move(v)}, drawer{std::move(handler)} {}

  /// Runs the draw handler, then draws the wrapped view.
  ///
  /// @param context Mutable drawing context.
  /// @param offset Accumulated offset from the root view.
  constexpr void draw(draw_context_type &context, offset_type offset) {
    drawer.func(context, offset, holder);
    holder.draw(context, offset);
  }

  /// Returns the wrapped view bounds.
  ///
  /// @return Bounds reported by the wrapped view.
  size_type bounds() const { return holder.bounds(); }
  /// Returns the wrapped view frame.
  ///
  /// @return Frame reported by the wrapped view.
  rect_type frame() const { return holder.frame(); }

  /// Forwards a down event to the wrapped view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the wrapped view consumes the event.
  bool event(typename gesture_traits::on_down_type parameter, offset_type offset) { return holder.event(parameter, offset); }
  /// Forwards a drag event to the wrapped view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  void event(typename gesture_traits::on_drag_type parameter, offset_type offset) { holder.event(parameter, offset); }
  /// Forwards an up event to the wrapped view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  void event(typename gesture_traits::on_up_type parameter, offset_type offset) { holder.event(parameter, offset); }
  /// Forwards an over event to the wrapped view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the wrapped view consumes the event.
  bool event(typename gesture_traits::on_over_type parameter, offset_type offset) { return holder.event(parameter, offset); }
  /// Forwards an out event to the wrapped view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  void event(typename gesture_traits::on_out_type parameter, offset_type offset) { holder.event(parameter, offset); }
  /// Forwards a double-click event to the wrapped view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the wrapped view consumes the event.
  bool event(typename gesture_traits::on_double_type parameter, offset_type offset) { return holder.event(parameter, offset); }
  /// Forwards a wheel event to the wrapped view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the wrapped view consumes the event.
  bool event(typename gesture_traits::on_wheel_type parameter, offset_type offset) { return holder.event(parameter, offset); }

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
  HandlerType drawer;
};

/// Deduces a surface decorator from a view and draw handler.
template <usagi::concepts::ui::viewable ViewType, usagi::concepts::ui::draw_handler HandlerType>
requires usagi::concepts::ui::transformable<ViewType>
surface(ViewType &&, HandlerType) -> surface<ViewType, HandlerType>;

namespace detail {
  /// Pipe payload used to attach a draw handler to a view.
  ///
  /// @tparam FunctionType Draw handler wrapper type.
  template <class FunctionType>
  struct surface_holder {
    /// Stored draw handler wrapper.
    FunctionType func;
  };

  template <class FunctionType>
  surface_holder(FunctionType) -> surface_holder<FunctionType>;
} // namespace detail

/// Attaches a draw handler to a view with the pipe operator.
///
/// @param v View to decorate.
/// @param holder Draw handler holder.
/// @return Draw-decorated view.
template <usagi::concepts::ui::viewable ViewType, usagi::concepts::ui::draw_handler HandlerType>
requires usagi::concepts::ui::transformable<ViewType>
inline constexpr decltype(auto) operator|(ViewType &&v,
                                          detail::surface_holder<HandlerType> &&holder) {
  return surface{std::forward<ViewType>(v), std::move(holder).func};
}

/// Creates a pipe payload containing a draw handler.
///
/// @param handler Draw handler wrapper created by `on_draw`.
/// @return Surface holder that can be piped into a view.
template <usagi::concepts::ui::draw_handler HandlerType>
inline constexpr decltype(auto) surfaced(HandlerType &&handler) {
  return detail::surface_holder<std::decay_t<HandlerType>>{std::forward<HandlerType>(handler)};
}

} // namespace usagi::ui
