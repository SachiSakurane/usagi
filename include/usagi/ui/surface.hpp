#pragma once

#include <utility>

#include <usagi/concepts/invocable.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>

namespace usagi::ui {
template <class FunctionType>
struct surface_holder {
  FunctionType func;
};

template <class FunctionType>
surface_holder(FunctionType) -> surface_holder<FunctionType>;

template <usagi::concepts::ui::viewable ViewType, class FunctionType>
requires usagi::concepts::invocable<FunctionType, typename ViewType::draw_context_type &,
                                    const ViewType &>
struct surface {
  using value_type = typename ViewType::value_type;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = typename ViewType::draw_context_type;
  using gesture_parameter_type = typename ViewType::gesture_parameter_type;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  surface(ViewType &&v, FunctionType f) : holder{std::move(v)}, drawer{f} {}

  void draw(draw_context_type &context) {
    drawer(context, holder);
    holder.draw(context);
  }

  size_type bounds() const { return holder.bounds(); }
  rect_type frame() const { return holder.frame(); }

  bool event(typename gesture_traits::on_down_type parameter) { return holder.event(parameter); }
  void event(typename gesture_traits::on_drag_type parameter) { holder.event(parameter); }
  void event(typename gesture_traits::on_up_type parameter) { holder.event(parameter); }
  bool event(typename gesture_traits::on_over_type parameter) { return holder.event(parameter); }
  void event(typename gesture_traits::on_out_type parameter) { holder.event(parameter); }
  bool event(typename gesture_traits::on_double_type parameter) { return holder.event(parameter); }
  bool event(typename gesture_traits::on_wheel_type parameter) { return holder.event(parameter); }

  void set_down(bool flag) { holder.set_down(flag); }
  void set_over(bool flag) { holder.set_over(flag); }
  [[nodiscard]] bool on_downed() const { return holder.on_downed(); }
  [[nodiscard]] bool on_overed() const { return holder.on_overed(); }

  void set_enabled(bool flag) { holder.set_enabled(flag); }
  [[nodiscard]] bool is_enabled() const { return holder.is_enabled(); }

private:
  ViewType holder;
  FunctionType drawer;
};

template <usagi::concepts::ui::viewable ViewType, class FunctionType>
surface(ViewType &&, FunctionType) -> surface<ViewType, FunctionType>;

template <usagi::concepts::ui::viewable ViewType, class FunctionType>
inline constexpr decltype(auto) operator|(ViewType &&v, surface_holder<FunctionType> &&holder) {
  return surface{std::forward<ViewType>(v), std::move(holder).func};
}

/**
 * Adapter for wrapping the surface
 *
 * @tparam FunctionType must be able to execute a function with
 * @code
 * invocable&lt;FunctionType, typename ViewType::draw_context_type &, const ViewType &&gt;
 * @endcode
 * as arguments.
 *
 * @param func to be wrapped by surface
 * @return surface_wrapper
 */
template <class FunctionType>
inline constexpr decltype(auto) surfaced(FunctionType &&func) {
  return surface_holder<FunctionType>{func};
}

} // namespace usagi::ui
