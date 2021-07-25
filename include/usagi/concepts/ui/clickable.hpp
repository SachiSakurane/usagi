#pragma once

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
};
} // namespace usagi::concepts::ui
