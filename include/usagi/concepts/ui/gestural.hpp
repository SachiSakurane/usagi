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
 * gesture できるやつ
 *
 * 終点は基本的に resolve(true を返して以降のレイヤーを無視すること) ができない
 */
template <class GesturalType>
concept gestural = requires(GesturalType &g) {
  typename GesturalType::mouse_parameter_type;

  {
    g.event(std::declval<typename usagi::type::mouse_traits<
                typename GesturalType::mouse_parameter_type>::on_down_type>())
    } -> std::same_as<bool>;

  g.event(std::declval<typename usagi::type::mouse_traits<
              typename GesturalType::mouse_parameter_type>::on_drag_type>());

  {
    g.event(std::declval<typename usagi::type::mouse_traits<
                typename GesturalType::mouse_parameter_type>::on_over_type>())
    } -> std::same_as<bool>;

  g.event(std::declval<typename usagi::type::mouse_traits<
              typename GesturalType::mouse_parameter_type>::on_up_type>());

  g.event(std::declval<typename usagi::type::mouse_traits<
              typename GesturalType::mouse_parameter_type>::on_out_type>());
  {
    g.event(std::declval<typename usagi::type::mouse_traits<
                typename GesturalType::mouse_parameter_type>::on_double_type>())
    } -> std::same_as<bool>;

  {
    g.event(std::declval<typename usagi::type::mouse_traits<
                typename GesturalType::mouse_parameter_type>::on_wheel_type>())
    } -> std::same_as<bool>;

  g.set_mouse_down(std::declval<bool>());
  g.set_mouse_over(std::declval<bool>());

  { g.is_mouse_downed() } -> std::same_as<bool>;
  { g.is_mouse_overed() } -> std::same_as<bool>;
};
} // namespace usagi::concepts::ui
