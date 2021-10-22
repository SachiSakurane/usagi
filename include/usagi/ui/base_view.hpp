#pragma once

#include <iterator>
#include <map>

#include <usagi/concepts/geometry.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/geometry/rect/function.hpp>
#include <usagi/type/mouse.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::ui {
template <usagi::utility::arithmetic ValueType, class DrawContextType, class MouseParameterType>
class base_view {
public:
  using value_type = ValueType;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = DrawContextType;
  using mouse_parameter_type = MouseParameterType;
  using mouse_traits = typename usagi::type::mouse_traits<mouse_parameter_type>;
  using view_type = usagi::ui::view<value_type, draw_context_type, mouse_parameter_type>;

  using children_mapped_type = view_type;
  using children_key_type = size_t;
  using children_type = std::map<children_key_type, children_mapped_type>;
  using children_value_type = typename children_type::value_type;

  base_view() = default;
  explicit base_view(const usagi::concepts::geometry::rect_concept auto &frame) : content{frame} {}

  base_view(base_view &&) noexcept = default;
  base_view &operator=(base_view &&) noexcept = default;

  virtual ~base_view() = default;

  virtual void draw(draw_context_type &context) {
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_enabled()) {
        child.draw(context);
      }
    }
  }

  virtual size_type bounds() const { return content.size(); }
  virtual rect_type frame() const { return content; }

  virtual void event(typename mouse_traits::on_down_type mouse) {
    set_mouse_down(true);
    auto point = point_type{mouse.x, mouse.y};
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        child.set_mouse_down(true);
        child.event(mouse);
      }
    }
  }

  virtual void event(typename mouse_traits::on_drag_type mouse) {
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_mouse_downed()) {
        child.event(mouse);
      }
    }
  }

  virtual void event(typename mouse_traits::on_up_type mouse) {
    set_mouse_down(false);
    auto point = point_type{mouse.x, mouse.y};
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_mouse_downed()) {
        child.set_mouse_down(false);
        child.event(mouse);
      }
    }
  }

  // ここに来るイベントは contain を想定する
  virtual void event(typename mouse_traits::on_over_type mouse) {
    set_mouse_over(true);
    auto point = point_type{mouse.x, mouse.y};
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        child.set_mouse_over(true);
        child.event(mouse);
      } else if (child.is_mouse_overed() == true) {
        child.set_mouse_over(false);
        child.event(typename mouse_traits::on_out_type{mouse});
      }
    }
  }

  virtual void event(typename mouse_traits::on_out_type mouse) {
    set_mouse_over(false);
    for (auto &value : children) {
      auto &child = value.second;
      child.event(mouse);
    }
  }

  virtual void event(typename mouse_traits::on_double_click_type mouse) {
    auto point = point_type{mouse.x, mouse.y};
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point))
        child.event(mouse);
    }
  }

  virtual void event(typename mouse_traits::on_wheel_type mouse) {
    auto point = point_type{mouse.x, mouse.y};
    for (auto &value : children) {
      auto &child = value.second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point))
        child.event(mouse);
    }
  }

  virtual void set_mouse_down(bool flag) { mouse_downed = flag; }
  virtual void set_mouse_over(bool flag) { mouse_overed = flag; }

  [[nodiscard]] virtual bool is_mouse_downed() const { return mouse_downed; }
  [[nodiscard]] virtual bool is_mouse_overed() const { return mouse_overed; }

  virtual children_value_type &add_sub_view(children_mapped_type &&sub_view) {
    const auto current_index = children_next_index;
    children_next_index += 1;
    return *children.try_emplace(std::end(children), current_index,
                                 std::forward<children_mapped_type>(sub_view));
  }

  virtual children_mapped_type &get_sub_view(children_key_type index) {
    assert(children.find(index) != std::end(children));
    return children.at(index);
  }

  virtual bool remove_sub_view(children_key_type index) {
    if (auto it = children.find(index); it != std::end(children))
    {
      children.erase(it);
      return true;
    }
    return false;
  }

  [[nodiscard]] virtual size_t sub_view_size() const { return children.size(); }

  virtual void set_enabled(bool flag) { enabled = flag; }
  [[nodiscard]] virtual bool is_enabled() const { return enabled; }

private:
  rect_type content{};
  size_t children_next_index{0};
  children_type children;
  bool mouse_downed{false};
  bool mouse_overed{false};
  bool enabled{true};
};
} // namespace usagi::ui
