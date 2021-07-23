#pragma once

#include <utility>

#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>

namespace usagi::ui {
template <class FunctionType>
struct surface_wrapper {
  template <usagi::concepts::ui::viewable ViewType>
  constexpr void operator()(typename ViewType::draw_context_type &c, const ViewType &v) {
    func(c, v);
  }

  FunctionType func;
};

template <usagi::concepts::ui::viewable ViewType, class FunctionType>
struct surface final {
  using value_type = typename ViewType::value_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = typename ViewType::draw_context_type;
  using mouse_traits = typename usagi::type::mouse_traits<value_type>;
  using view_type = typename ViewType::view_type;

  surface(ViewType &&v, FunctionType f)
      : holder{std::move(v)}, drawer{f} {}

  void draw(draw_context_type &context) {
    drawer(context, holder);
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
  ViewType holder;
  FunctionType drawer;
};

template <usagi::concepts::ui::viewable ViewType, class FunctionType>
surface(ViewType &&, FunctionType) -> surface<ViewType, FunctionType>;

template <usagi::concepts::ui::viewable ViewType, class FunctionType>
inline constexpr decltype(auto) operator|(ViewType &&v, surface_wrapper<FunctionType> func) {
  return surface{std::forward<ViewType>(v), func};
}

template <class FunctionType>
inline constexpr decltype(auto) surfaced(FunctionType func) {
  return surface_wrapper<FunctionType>{func};
}

} // namespace usagi::ui
