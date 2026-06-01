#pragma once

#include <cassert>
#include <cstddef>
#include <iterator>
#include <map>
#include <utility>

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry.hpp>
#include <usagi/geometry.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/view.hpp>

namespace usagi::ui {
template <usagi::concepts::arithmetic ValueType, class DrawContextType, class GestureParameterType>
struct view_stack : public usagi::ui::base_view<ValueType, DrawContextType, GestureParameterType> {
  using base_view_type = usagi::ui::base_view<ValueType, DrawContextType, GestureParameterType>;

  using value_type = typename base_view_type::value_type;
  using point_type = typename base_view_type::point_type;
  using rect_type = typename base_view_type::rect_type;
  using size_type = typename base_view_type::size_type;
  using draw_context_type = typename base_view_type::draw_context_type;
  using offset_type = typename base_view_type::offset_type;
  using gesture_parameter_type = typename base_view_type::gesture_parameter_type;
  using gesture_traits = typename base_view_type::gesture_traits;

  using child_view_type = usagi::ui::view<value_type, draw_context_type, gesture_parameter_type>;
  using child_view_key_type = size_t;
  using child_view_map_type = std::map<child_view_key_type, child_view_type>;
  using child_view_value_type = typename child_view_map_type::value_type;

  view_stack() = default;

  constexpr explicit view_stack(const usagi::concepts::geometry::rect_concept auto &frame)
      : base_view_type{frame} {}

  void draw(draw_context_type &context, offset_type offset) override {
    for (auto &value : child_views) {
      auto &child = value.second;
      if (child.is_enabled()) {
        child.draw(context, offset + offset_type{child.frame().l(), child.frame().t()});
      }
    }
  }

  bool event(typename gesture_traits::on_down_type parameter, offset_type offset) override {
    this->set_down(true);
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

  void event(typename gesture_traits::on_drag_type parameter, offset_type offset) override {
    for (auto it = std::rbegin(child_views); it != std::rend(child_views); ++it) {
      auto &child = it->second;
      if (child.is_downed()) {
        child.event(parameter, offset + offset_type{child.frame().l(), child.frame().t()});
      }
    }
  }

  void event(typename gesture_traits::on_up_type parameter, offset_type offset) override {
    this->set_down(false);
    for (auto it = std::rbegin(child_views); it != std::rend(child_views); ++it) {
      auto &child = it->second;
      if (child.is_downed()) {
        child.set_down(false);
        child.event(parameter, offset + offset_type{child.frame().l(), child.frame().t()});
      }
    }
  }

  // ここに来るイベントは contain を想定する
  bool event(typename gesture_traits::on_over_type parameter, offset_type offset) override {
    this->set_over(true);
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

  void event(typename gesture_traits::on_out_type parameter, offset_type offset) override {
    this->set_over(false);
    for (auto it = std::rbegin(child_views); it != std::rend(child_views); ++it) {
      auto &child = it->second;
      child.event(parameter, offset + offset_type{child.frame().l(), child.frame().t()});
    }
  }

  bool event(typename gesture_traits::on_double_type parameter, offset_type offset) override {
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

  bool event(typename gesture_traits::on_wheel_type parameter, offset_type offset) override {
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
  size_t children_next_index{0};
  child_view_map_type child_views;
};

} // namespace usagi::ui
