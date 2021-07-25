#pragma once

#include <utility>

#include <usagi/type/mouse.hpp>

namespace usagi::concepts::ui {
/**
 * click できるやつ
 */
template <class ClickableType>
concept clickable = requires(ClickableType &c) {
  typename ClickableType::value_type;

  c.event(usagi::type::mouse::on_down{std::declval<typename ClickableType::value_type>(),
                                      std::declval<typename ClickableType::value_type>()});

  c.event(usagi::type::mouse::on_drag{std::declval<typename ClickableType::value_type>(),
                                      std::declval<typename ClickableType::value_type>()});

  c.event(usagi::type::mouse::on_up{std::declval<typename ClickableType::value_type>(),
                                    std::declval<typename ClickableType::value_type>()});
};
} // namespace usagi::concepts::ui
