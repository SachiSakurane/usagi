#pragma once

#include <concepts>
#include <type_traits>

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry/point_concept.hpp>

namespace usagi::concepts::type {
/// Matches gesture parameter payloads used by UI gesture events.
///
/// @tparam GesturalParameterType Type to test.
template <class GesturalParameterType>
concept gestural_parameter = requires(GesturalParameterType g) {
  requires usagi::concepts::arithmetic<typename GesturalParameterType::value_type>;

  { g.position } -> usagi::concepts::geometry::point_concept;
  requires std::same_as<typename std::remove_cvref_t<decltype(g.position)>::value_type,
                        typename GesturalParameterType::value_type>;
  { g.wheel_delta } -> std::same_as<typename GesturalParameterType::value_type &>;
  { g.l } -> std::same_as<bool &>;
  { g.r } -> std::same_as<bool &>;
  { g.shift } -> std::same_as<bool &>;
  { g.ctrl } -> std::same_as<bool &>;
  { g.alt } -> std::same_as<bool &>;
};
} // namespace usagi::concepts::type
