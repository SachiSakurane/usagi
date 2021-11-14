#pragma once

#include <usagi/ui/detail/base_view_gesture.hpp>
#include <usagi/ui/detail/base_view_hierarchy.hpp>

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>

namespace usagi::ui {
template <usagi::utility::arithmetic ValueType, class DrawContextType, class MouseParameterType>
class base_view {
  using base_view_click_type = usagi::ui::detail::base_view_gesture<ValueType, MouseParameterType>;

public:
  using value_type = ValueType;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = DrawContextType;
  using mouse_parameter_type = MouseParameterType;
  using mouse_traits = typename usagi::type::mouse_traits<mouse_parameter_type>;
  using view_type = usagi::ui::view<value_type, draw_context_type, MouseParameterType>;

  using base_view_hierarch_type = usagi::ui::detail::base_view_hierarchy<view_type>;
  using children_mapped_type = typename base_view_hierarch_type::children_mapped_type;
  using children_key_type = typename base_view_hierarch_type::children_key_type;
  using children_type = typename base_view_hierarch_type::children_type;
  using children_value_type = typename base_view_hierarch_type::children_value_type;

  base_view() = default;
  explicit base_view(const usagi::concepts::geometry::rect_concept auto &frame) : content{frame} {}

  base_view(base_view &&) noexcept = default;
  base_view &operator=(base_view &&) noexcept = default;

  virtual ~base_view() = default;

  virtual void draw(draw_context_type &context) {
    for (auto &value : hierarchy.get_children()) {
      auto &child = value.second;
      if (child.is_enabled()) {
        child.draw(context);
      }
    }
  }

  virtual size_type bounds() const { return content.size(); }
  virtual rect_type frame() const { return content; }

  virtual bool event(typename mouse_traits::on_down_type mouse) {
    return gesture.on_event(mouse, hierarchy.get_children());
  }
  virtual void event(typename mouse_traits::on_drag_type mouse) {
    gesture.on_event(mouse, hierarchy.get_children());
  }
  virtual void event(typename mouse_traits::on_up_type mouse) {
    gesture.on_event(mouse, hierarchy.get_children());
  }
  virtual bool event(typename mouse_traits::on_over_type mouse) {
    return gesture.on_event(mouse, hierarchy.get_children());
  }
  virtual void event(typename mouse_traits::on_out_type mouse) {
    gesture.on_event(mouse, hierarchy.get_children());
  }
  virtual bool event(typename mouse_traits::on_double_type mouse) {
    return gesture.on_event(mouse, hierarchy.get_children());
  }
  virtual bool event(typename mouse_traits::on_wheel_type mouse) {
    return gesture.on_event(mouse, hierarchy.get_children());
  }

  virtual void set_mouse_down(bool flag) { gesture.set_mouse_down(flag); }
  virtual void set_mouse_over(bool flag) { gesture.set_mouse_over(flag); }

  [[nodiscard]] virtual bool is_mouse_downed() const { return gesture.is_mouse_downed(); }
  [[nodiscard]] virtual bool is_mouse_overed() const { return gesture.is_mouse_overed(); }

  virtual children_value_type &add_sub_view(children_mapped_type &&sub_view) {
    return hierarchy.add_sub_view(std::forward<children_mapped_type>(sub_view));
  }
  virtual children_mapped_type &get_sub_view(children_key_type index) {
    return hierarchy.get_sub_view(index);
  }
  virtual bool remove_sub_view(children_key_type index) { return hierarchy.remove_sub_view(index); }

  [[nodiscard]] virtual size_t sub_view_size() const { return hierarchy.sub_view_size(); }

  virtual void set_enabled(bool flag) { enabled = flag; }
  [[nodiscard]] virtual bool is_enabled() const { return enabled; }

private:
  base_view_click_type gesture;
  base_view_hierarch_type hierarchy;
  rect_type content{};
  bool enabled{true};
};
} // namespace usagi::ui
