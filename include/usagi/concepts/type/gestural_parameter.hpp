#pragma once

#include <usagi/concepts/arithmetic.hpp>

namespace usagi::concepts::type {
template <class GesturalParameterType>
concept gestural_parameter = requires(GesturalParameterType g) {
  { g.x } -> usagi::concepts::arithmetic;
  { g.y } -> usagi::concepts::arithmetic;
  { g.d } -> usagi::concepts::arithmetic;
};
} // namespace usagi::concepts::type
