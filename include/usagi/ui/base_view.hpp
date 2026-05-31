#pragma once

#include <usagi/concepts/geometry.hpp>
#include <usagi/geometry/rect/function.hpp>
#include <usagi/ui/view_interface.hpp>

namespace usagi::ui {
template <usagi::concepts::arithmetic ValueType, class DrawContextType, class GestureParameterType>
class base_view : public view_interface<ValueType, DrawContextType, GestureParameterType> {
  using view_interface_type = view_interface<ValueType, DrawContextType, GestureParameterType>;

public:
  using value_type = typename view_interface_type::value_type;
  using point_type = typename view_interface_type::point_type;
  using rect_type = typename view_interface_type::rect_type;
  using size_type = typename view_interface_type::size_type;
  using draw_context_type = typename view_interface_type::draw_context_type;
  using offset_type = typename view_interface_type::offset_type;
  using gesture_parameter_type = typename view_interface_type::gesture_parameter_type;
  using gesture_traits = typename view_interface_type::gesture_traits;

  base_view() = default;
  constexpr explicit base_view(const usagi::concepts::geometry::rect_concept auto &frame)
      : content{frame} {}

  constexpr ~base_view() override = default;

  constexpr void draw(draw_context_type &context, offset_type offset) override {}

  constexpr bool event(typename gesture_traits::on_down_type g, offset_type offset) override {
    if (!ignore_events && usagi::geometry::contain(frame(), g.position)) {
      set_down(true);
      return true;
    }
    return false;
  }
  constexpr void event(typename gesture_traits::on_drag_type g, offset_type offset) override {}
  constexpr void event(typename gesture_traits::on_up_type g, offset_type offset) override {
    if (!ignore_events && is_downed()) {
      set_down(false);
    }
  }
  constexpr bool event(typename gesture_traits::on_over_type g, offset_type offset) override {
    if (!ignore_events && usagi::geometry::contain(frame(), g.position)) {
      set_over(true);
      return true;
    }
    return false;
  }
  constexpr void event(typename gesture_traits::on_out_type g, offset_type offset) override {
    if (is_overed()) {
      set_over(false);
    }
  }
  constexpr bool event(typename gesture_traits::on_double_type g, offset_type offset) override {
    return false;
  }
  constexpr bool event(typename gesture_traits::on_wheel_type g, offset_type offset) override {
    return false;
  }

  constexpr void set_down(bool flag) override { parameter_downed = flag; }
  constexpr void set_over(bool flag) override { parameter_overed = flag; }

  [[nodiscard]] constexpr bool is_downed() const override { return parameter_downed; }
  [[nodiscard]] constexpr bool is_overed() const override { return parameter_overed; }

  [[nodiscard]] constexpr size_type bounds() const override { return content.size(); }
  [[nodiscard]] constexpr rect_type frame() const override { return content; }

  constexpr void set_enabled(bool flag) override { enabled = flag; }
  [[nodiscard]] constexpr bool is_enabled() const override { return enabled; }

  void set_ignore_events(bool flag) { ignore_events = flag; }
  [[nodiscard]] bool is_ignoring_events() const { return ignore_events; }

private:
  rect_type content{};
  bool ignore_events{false};
  bool enabled{true};
  bool parameter_downed{false};
  bool parameter_overed{false};
};
} // namespace usagi::ui
