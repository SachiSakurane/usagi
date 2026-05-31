#pragma once

#include <cassert>
#include <cstddef>
#include <iterator>
#include <map>
#include <utility>

#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry.hpp>
#include <usagi/ui/view.hpp>

namespace usagi::ui {
template <usagi::concepts::ui::viewable ViewType>
struct view_stack {
  using value_type = typename ViewType::value_type;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = typename ViewType::draw_context_type;
  using offset_type = typename ViewType::offset_type;
  using gesture_parameter_type = typename ViewType::gesture_parameter_type;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  using child_view_type = usagi::ui::view<value_type, draw_context_type, gesture_parameter_type>;
  using child_view_key_type = size_t;
  using child_view_map_type = std::map<child_view_key_type, child_view_type>;
  using child_view_value_type = typename child_view_map_type::value_type;

  explicit view_stack(ViewType &&v) : holder{std::move(v)} {}

  virtual void draw(draw_context_type &context, offset_type offset) {
    for (auto &value : child_views) {
      auto &child = value.second;
      if (child.is_enabled()) {
        child.draw(context, offset + offset_type{child.frame().l(), child.frame().t()});
      }
    }
  }

  virtual size_type bounds() const { return holder.bounds(); }
  virtual rect_type frame() const { return holder.frame(); }

  virtual bool event(typename gesture_traits::on_down_type parameter, offset_type offset) {
    set_down(true);
    for (auto it = std::rbegin(child_views); it != std::rend(child_views); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), parameter.position)) {
        child.set_down(true);
        if (child.event(parameter, offset + offset_type{child.frame().l(), child.frame().t()})) {
          return true;
        }
      }
    }
    return false;
  }

  virtual void event(typename gesture_traits::on_drag_type parameter, offset_type offset) {
    for (auto it = std::rbegin(child_views); it != std::rend(child_views); ++it) {
      auto &child = it->second;
      if (child.is_downed()) {
        child.event(parameter, offset + offset_type{child.frame().l(), child.frame().t()});
      }
    }
  }

  virtual void event(typename gesture_traits::on_up_type parameter, offset_type offset) {
    set_down(false);
    for (auto it = std::rbegin(child_views); it != std::rend(child_views); ++it) {
      auto &child = it->second;
      if (child.is_downed()) {
        child.set_down(false);
        child.event(parameter, offset + offset_type{child.frame().l(), child.frame().t()});
      }
    }
  }

  // ここに来るイベントは contain を想定する
  virtual bool event(typename gesture_traits::on_over_type parameter, offset_type offset) {
    set_over(true);
    auto is_resolved = false;
    for (auto it = std::rbegin(child_views); it != std::rend(child_views); ++it) {
      auto &child = it->second;
      if (!is_resolved && child.is_enabled() &&
          usagi::geometry::contain(child.frame(), parameter.position)) {
        child.set_over(true);
        is_resolved =
            child.event(parameter, offset + offset_type{child.frame().l(), child.frame().t()});
      } else if (child.is_overed() == true) {
        child.set_over(false);
        child.event(parameter, offset + offset_type{child.frame().l(), child.frame().t()});
      }
    }
    return is_resolved;
  }

  virtual void event(typename gesture_traits::on_out_type parameter, offset_type offset) {
    set_over(false);
    for (auto it = std::rbegin(child_views); it != std::rend(child_views); ++it) {
      auto &child = it->second;
      child.event(parameter, offset + offset_type{child.frame().l(), child.frame().t()});
    }
  }

  virtual bool event(typename gesture_traits::on_double_type parameter, offset_type offset) {
    for (auto it = std::rbegin(child_views); it != std::rend(child_views); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), parameter.position)) {
        if (child.event(parameter, offset + offset_type{child.frame().l(), child.frame().t()})) {
          return true;
        }
      }
    }
    return false;
  }

  virtual bool event(typename gesture_traits::on_wheel_type parameter, offset_type offset) {
    for (auto it = std::rbegin(child_views); it != std::rend(child_views); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), parameter.position)) {
        if (child.event(parameter, offset + offset_type{child.frame().l(), child.frame().t()})) {
          return true;
        }
      }
    }
    return false;
  }

  virtual void set_down(bool flag) { holder.set_down(flag); }
  virtual void set_over(bool flag) { holder.set_over(flag); }

  [[nodiscard]] virtual bool is_downed() const { return holder.is_downed(); }
  [[nodiscard]] virtual bool is_overed() const { return holder.is_overed(); }

  virtual void set_enabled(bool flag) { holder.set_enabled(flag); }
  [[nodiscard]] virtual bool is_enabled() const { return holder.is_enabled(); }

  child_view_value_type &add_child_view(child_view_type &&child_view) {
    const auto current_index = children_next_index;
    children_next_index += 1;
    return *child_views.try_emplace(std::end(child_views), current_index,
                                    std::forward<child_view_type>(child_view));
  }

  typename child_view_map_type::mapped_type &get_child_view(child_view_key_type index) {
    assert(child_views.find(index) != std::end(child_views));
    return child_views.at(index);
  }

  bool remove_child_view(child_view_key_type index) {
    if (auto it = child_views.find(index); it != std::end(child_views)) {
      child_views.erase(it);
      return true;
    }
    return false;
  }

  [[nodiscard]] size_t child_view_size() const { return child_views.size(); }

private:
  ViewType holder;
  size_t children_next_index{0};
  child_view_map_type child_views;
};

} // namespace usagi::ui
