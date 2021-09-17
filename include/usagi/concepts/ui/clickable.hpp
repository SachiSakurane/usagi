#pragma once

#include <concepts>
#include <utility>

#include <usagi/type/mouse.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::concepts::ui {
template <class MouseParameterType>
concept mouse_parameter = requires(MouseParameterType &m) {
  { m.x } -> usagi::utility::arithmetic;
  { m.y } -> usagi::utility::arithmetic;
};

/**
 * click できるやつ
 */
template <class ClickableType>
concept clickable = requires(ClickableType &c) {
  typename ClickableType::mouse_parameter_type;

  c.event(std::declval<typename usagi::type::mouse_traits<
              typename ClickableType::mouse_parameter_type>::on_down_type>());
  c.event(std::declval<typename usagi::type::mouse_traits<
              typename ClickableType::mouse_parameter_type>::on_drag_type>());
  c.event(std::declval<typename usagi::type::mouse_traits<
              typename ClickableType::mouse_parameter_type>::on_over_type>());
  c.event(std::declval<typename usagi::type::mouse_traits<
              typename ClickableType::mouse_parameter_type>::on_up_type>());
  c.event(std::declval<typename usagi::type::mouse_traits<
              typename ClickableType::mouse_parameter_type>::on_out_type>());

  c.set_mouse_down(std::declval<bool>());
  c.set_mouse_over(std::declval<bool>());

  { c.is_mouse_downed() } -> std::same_as<bool>;
  { c.is_mouse_overed() } -> std::same_as<bool>;
};
} // namespace usagi::concepts::ui
