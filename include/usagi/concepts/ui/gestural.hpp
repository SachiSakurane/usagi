#pragma once

#include <concepts>
#include <utility>

#include <usagi/type/gesture.hpp>

namespace usagi::concepts::ui {
/// Matches types that can receive all UI gesture event variants.
///
/// @tparam GesturalType Type to test.
template <class GesturalType>
concept gestural = requires(GesturalType &g) {
  typename GesturalType::offset_type;
  {
    g.event(std::declval<typename usagi::type::gesture_traits<
                typename GesturalType::gesture_parameter_type>::on_down_type>(),
            std::declval<typename GesturalType::offset_type>())
  } -> std::same_as<bool>;

  g.event(std::declval<typename usagi::type::gesture_traits<
              typename GesturalType::gesture_parameter_type>::on_drag_type>(),
          std::declval<typename GesturalType::offset_type>());

  {
    g.event(std::declval<typename usagi::type::gesture_traits<
                typename GesturalType::gesture_parameter_type>::on_over_type>(),
            std::declval<typename GesturalType::offset_type>())
  } -> std::same_as<bool>;

  g.event(std::declval<typename usagi::type::gesture_traits<
              typename GesturalType::gesture_parameter_type>::on_up_type>(),
          std::declval<typename GesturalType::offset_type>());

  g.event(std::declval<typename usagi::type::gesture_traits<
              typename GesturalType::gesture_parameter_type>::on_out_type>(),
          std::declval<typename GesturalType::offset_type>());
  {
    g.event(std::declval<typename usagi::type::gesture_traits<
                typename GesturalType::gesture_parameter_type>::on_double_type>(),
            std::declval<typename GesturalType::offset_type>())
  } -> std::same_as<bool>;

  {
    g.event(std::declval<typename usagi::type::gesture_traits<
                typename GesturalType::gesture_parameter_type>::on_wheel_type>(),
            std::declval<typename GesturalType::offset_type>())
  } -> std::same_as<bool>;

  g.set_down(std::declval<bool>());
  g.set_over(std::declval<bool>());

  { g.is_downed() } -> std::same_as<bool>;
  { g.is_overed() } -> std::same_as<bool>;
};
} // namespace usagi::concepts::ui
