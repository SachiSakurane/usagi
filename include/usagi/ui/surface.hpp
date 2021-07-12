#pragma once

#include <functional>
#include <type_traits>

#include <usagi/concepts/ui/viewable.hpp>

namespace usagi::ui {

namespace detail {
  template <usagi::concepts::ui::viewable ViewType>
  using surface_func_type =
      std::function<void(typename ViewType::draw_context_type::draw_type &, const ViewType &)>;
} // namespace detail

template <usagi::concepts::ui::viewable ViewType>
struct surface final {
  using value_type = typename ViewType::value_type;
  using point_type = typename ViewType::point_type;
  using rect_type = typename ViewType::rect_type;
  using size_type = typename ViewType::size_type;
  using draw_context_type = typename ViewType::draw_context_type;
  using mouse_traits = typename ViewType::mouse_traits;
  using view_type = surface<ViewType>;

  template <class... Args>
  explicit surface(usagi::ui::detail::surface_func_type<ViewType> &&f, Args &&...args)
      : func{std::forward<usagi::ui::detail::surface_func_type<ViewType>>(f)},
        holder{std::forward<Args>(args)...} {}

  void draw(draw_context_type &context) {
    context.draw([this](typename ViewType::draw_context_type::draw_type &d) { func(d, *this); });
    holder.draw(context);
  }

  size_type bounds() const { return holder.bounds(); }
  rect_type frame() const { return holder.frame(); }

  void event(typename mouse_traits::on_down_type mouse) { holder.event(mouse); }
  void event(typename mouse_traits::on_drag_type mouse) { holder.event(mouse); }
  void event(typename mouse_traits::on_up_type mouse) { holder.event(mouse); }
  void event(typename mouse_traits::on_over_type mouse) { holder.event(mouse); }

  view_type &add_sub_view(view_type &&sub_view) {
    return holder.add_sub_view(std::forward<view_type>(sub_view));
  }

private:
  usagi::ui::detail::surface_func_type<ViewType> func;
  ViewType holder;
};

template <usagi::concepts::ui::viewable ViewType, class... ConstructorArgs>
inline constexpr decltype(auto) surfaced(usagi::ui::detail::surface_func_type<ViewType> &&draw_func,
                                         ConstructorArgs &&...args) {
  return usagi::ui::surface<ViewType>{
      std::forward<usagi::ui::detail::surface_func_type<ViewType>>(draw_func),
      std::forward<ConstructorArgs>(args)...};
}
} // namespace usagi::ui
