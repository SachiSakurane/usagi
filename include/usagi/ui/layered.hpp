#pragma once

#include <map>
#include <tuple>

#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry.hpp>

namespace usagi::ui {
template <usagi::concepts::ui::viewable ViewType>
struct layer {
  using value_type = typename ViewType::value_type;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = typename ViewType::draw_context_type;
  using gesture_parameter_type = typename ViewType::gesture_parameter_type;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  using sub_view_type = usagi::ui::view<value_type, draw_context_type, gesture_parameter_type>;
  using sub_view_key_type = size_t;
  using sub_view_map_type = std::map<sub_view_key_type, sub_view_type>;

  explicit layer(ViewType &&v) : holder{std::move(v)} {}

  virtual void draw(draw_context_type &context) {
    for (auto &value : sub_views) {
      auto &child = value.second;
      if (child.is_enabled()) {
        child.draw(context);
      }
    }
  }

  virtual size_type bounds() const { return holder.bounds(); }
  virtual rect_type frame() const { return holder.frame(); }

  virtual bool event(typename gesture_traits::on_down_type parameter) {
    set_down(true);
    auto point = point_type{parameter.x, parameter.y};
    for (auto it = std::rbegin(sub_views); it != std::rend(sub_views); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        child.set_down(true);
        if (child.event(parameter)) {
          return true;
        }
      }
    }
    return false;
  }

  virtual void event(typename gesture_traits::on_drag_type parameter) {
    for (auto it = std::rbegin(sub_views); it != std::rend(sub_views); ++it) {
      auto &child = it->second;
      if (child.on_downed()) {
        child.event(parameter);
      }
    }
  }

  virtual void event(typename gesture_traits::on_up_type parameter) {
    set_down(false);
    auto point = point_type{parameter.x, parameter.y};
    for (auto it = std::rbegin(sub_views); it != std::rend(sub_views); ++it) {
      auto &child = it->second;
      if (child.on_downed()) {
        child.set_down(false);
        child.event(parameter);
      }
    }
  }

  // ここに来るイベントは contain を想定する
  virtual bool event(typename gesture_traits::on_over_type parameter) {
    set_over(true);
    auto point = point_type{parameter.x, parameter.y};
    auto is_resolved = false;
    for (auto it = std::rbegin(sub_views); it != std::rend(sub_views); ++it) {
      auto &child = it->second;
      if (!is_resolved && child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        child.set_over(true);
        is_resolved = child.event(parameter);
      } else if (child.on_overed() == true) {
        child.set_over(false);
        child.event(typename gesture_traits::on_out_type{parameter});
      }
    }
    return is_resolved;
  }

  virtual void event(typename gesture_traits::on_out_type parameter) {
    set_over(false);
    for (auto it = std::rbegin(sub_views); it != std::rend(sub_views); ++it) {
      auto &child = it->second;
      child.event(parameter);
    }
  }

  virtual bool event(typename gesture_traits::on_double_type parameter) {
    auto point = point_type{parameter.x, parameter.y};
    for (auto it = std::rbegin(sub_views); it != std::rend(sub_views); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        if (child.event(parameter)) {
          return true;
        }
      }
    }
    return false;
  }

  virtual bool event(typename gesture_traits::on_wheel_type parameter) {
    auto point = point_type{parameter.x, parameter.y};
    for (auto it = std::rbegin(sub_views); it != std::rend(sub_views); ++it) {
      auto &child = it->second;
      if (child.is_enabled() && usagi::geometry::contain(child.frame(), point)) {
        if (child.event(parameter)) {
          return true;
        }
      }
    }
    return false;
  }

  virtual void set_down(bool flag) { holder.set_down(flag); }
  virtual void set_over(bool flag) { holder.set_over(flag); }

  [[nodiscard]] virtual bool on_downed() const { return holder.on_downed(); }
  [[nodiscard]] virtual bool on_overed() const { return holder.on_overed(); }

  virtual void set_enabled(bool flag) { holder.set_enabled(flag); }
  [[nodiscard]] virtual bool is_enabled() const { return holder.is_enabled(); }

  typename sub_view_map_type::value_type &add_sub_view(sub_view_type &&sub_view) {
    const auto current_index = children_next_index;
    children_next_index += 1;
    return *sub_views.try_emplace(std::end(sub_views), current_index,
                                  std::forward<sub_view_type>(sub_view));
  }

  typename sub_view_map_type::mapped_type &get_sub_view(sub_view_key_type index) {
    assert(sub_views.find(index) != std::end(sub_views));
    return sub_views.at(index);
  }

  bool remove_sub_view(sub_view_key_type index) {
    if (auto it = sub_views.find(index); it != std::end(sub_views)) {
      sub_views.erase(it);
      return true;
    }
    return false;
  }

  [[nodiscard]] size_t sub_view_size() const { return sub_views.size(); }

private:
  ViewType holder;
  size_t children_next_index{0};
  sub_view_map_type sub_views;
};

} // namespace usagi::ui
