#pragma once

#include <concepts>
#include <utility>

#include <usagi/concepts/type/gestural_parameter.hpp>
#include <usagi/type/gesture.hpp>

namespace usagi::concepts::ui {
/**
 * gesture できるやつ
 *
 * 終点は基本的に resolve(true を返して以降のレイヤーを無視すること) ができない
 */
template <class GesturalType>
concept gestural = requires(GesturalType &g) {
  requires usagi::concepts::type::gestural_parameter<typename GesturalType::gesture_parameter_type>;
  {
    g.event(std::declval<typename usagi::type::gesture_traits<
                typename GesturalType::gesture_parameter_type>::on_down_type>())
    } -> std::same_as<bool>;

  g.event(std::declval<typename usagi::type::gesture_traits<
              typename GesturalType::gesture_parameter_type>::on_drag_type>());

  {
    g.event(std::declval<typename usagi::type::gesture_traits<
                typename GesturalType::gesture_parameter_type>::on_over_type>())
    } -> std::same_as<bool>;

  g.event(std::declval<typename usagi::type::gesture_traits<
              typename GesturalType::gesture_parameter_type>::on_up_type>());

  g.event(std::declval<typename usagi::type::gesture_traits<
              typename GesturalType::gesture_parameter_type>::on_out_type>());
  {
    g.event(std::declval<typename usagi::type::gesture_traits<
                typename GesturalType::gesture_parameter_type>::on_double_type>())
    } -> std::same_as<bool>;

  {
    g.event(std::declval<typename usagi::type::gesture_traits<
                typename GesturalType::gesture_parameter_type>::on_wheel_type>())
    } -> std::same_as<bool>;

  g.set_down(std::declval<bool>());
  g.set_over(std::declval<bool>());

  { g.on_downed() } -> std::same_as<bool>;
  { g.on_overed() } -> std::same_as<bool>;
};
} // namespace usagi::concepts::ui
