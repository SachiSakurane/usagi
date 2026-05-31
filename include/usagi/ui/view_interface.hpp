#pragma once

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/type/gesture.hpp>

namespace usagi::ui {
template <usagi::concepts::arithmetic ValueType, class DrawContextType, class GestureParameterType>
class view_interface {
public:
  using value_type = ValueType;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = DrawContextType;
  using offset_type = point_type;
  using gesture_parameter_type = GestureParameterType;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  virtual constexpr ~view_interface() = default;

  virtual constexpr void draw(draw_context_type &context, offset_type offset) = 0;

  [[nodiscard]] virtual constexpr size_type bounds() const = 0;
  [[nodiscard]] virtual constexpr rect_type frame() const = 0;

  virtual constexpr bool event(typename gesture_traits::on_down_type g, offset_type offset) = 0;
  virtual constexpr void event(typename gesture_traits::on_drag_type g, offset_type offset) = 0;
  virtual constexpr void event(typename gesture_traits::on_up_type g, offset_type offset) = 0;
  virtual constexpr bool event(typename gesture_traits::on_over_type g, offset_type offset) = 0;
  virtual constexpr void event(typename gesture_traits::on_out_type g, offset_type offset) = 0;
  virtual constexpr bool event(typename gesture_traits::on_double_type g, offset_type offset) = 0;
  virtual constexpr bool event(typename gesture_traits::on_wheel_type g, offset_type offset) = 0;

  virtual constexpr void set_down(bool flag) = 0;
  virtual constexpr void set_over(bool flag) = 0;
  [[nodiscard]] virtual constexpr bool is_downed() const = 0;
  [[nodiscard]] virtual constexpr bool is_overed() const = 0;

  virtual constexpr void set_enabled(bool flag) = 0;
  [[nodiscard]] virtual constexpr bool is_enabled() const = 0;
};
} // namespace usagi::ui
