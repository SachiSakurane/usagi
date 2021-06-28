#pragma once

#include <concepts>
#include <utility>

#include <usagi/type/mouse.h>

namespace usagi::concepts
{
  /** 
   * clickできるやつ
  */
  template <class ClickableType>
  concept clickable = requires(ClickableType &c)
  {
    typename ClickableType::value_type;
    c.event(usagi::type::mouse::on_down{std::declval<ClickableType::value_type>(), std::declval<ClickableType::value_type>()});
    c.event(usagi::type::mouse::on_drag{std::declval<ClickableType::value_type>(), std::declval<ClickableType::value_type>()});
    c.event(usagi::type::mouse::on_up{std::declval<ClickableType::value_type>(), std::declval<ClickableType::value_type>()});
    c.event(usagi::type::mouse::on_over{std::declval<ClickableType::value_type>(), std::declval<ClickableType::value_type>()});
  };
}
