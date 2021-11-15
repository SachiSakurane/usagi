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
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = typename ViewType::draw_context_type;
  using gesture_parameter_type = typename ViewType::gesture_parameter_type;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;
  using view_type = typename ViewType::view_type;

  using children_type = typename ViewType::children_type;
  using children_key_type = typename ViewType::children_key_type;
  using children_mapped_type = typename ViewType::children_mapped_type;
  using children_value_type = typename ViewType::children_value_type;

  surface(ViewType &&v, FunctionType f) : holder{std::move(v)}, drawer{f} {}

  void draw(draw_context_type &context) {
    drawer(context, holder);
    holder.draw(context);
  }

  size_type bounds() const { return holder.bounds(); }
  rect_type frame() const { return holder.frame(); }

  bool event(typename gesture_traits::on_down_type mouse) { return holder.event(mouse); }
  void event(typename gesture_traits::on_drag_type mouse) { holder.event(mouse); }
  void event(typename gesture_traits::on_up_type mouse) { holder.event(mouse); }
  bool event(typename gesture_traits::on_over_type mouse) { return holder.event(mouse); }
  void event(typename gesture_traits::on_out_type mouse) { holder.event(mouse); }
  bool event(typename gesture_traits::on_double_type mouse) { return holder.event(mouse); }
  bool event(typename gesture_traits::on_wheel_type mouse) { return holder.event(mouse); }

  void set_mouse_down(bool flag) { holder.set_mouse_down(flag); }
  void set_mouse_over(bool flag) { holder.set_mouse_over(flag); }
  [[nodiscard]] bool is_mouse_downed() const { return holder.is_mouse_downed(); }
  [[nodiscard]] bool is_mouse_overed() const { return holder.is_mouse_overed(); }

  children_value_type &add_sub_view(children_mapped_type &&sub_view) {
    return holder.add_sub_view(std::forward<children_mapped_type>(sub_view));
  }

  children_mapped_type &get_sub_view(children_key_type index) { return holder.get_sub_view(index); }

  bool remove_sub_view(children_key_type index) { return holder.remove_sub_view(index); }

  [[nodiscard]] size_t sub_view_size() const { return holder.sub_view_size(); }

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
