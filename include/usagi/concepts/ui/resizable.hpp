#pragma once

#include <utility>

namespace usagi::concepts::ui {
/**
 * resize できるやつ
 */
template <class ResizableType>
concept resizable = requires(ResizableType &r) {
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
