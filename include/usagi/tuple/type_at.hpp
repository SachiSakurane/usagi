#pragma once

#include <tuple>
#include <utility>

#include <usagi/tuple/get_index.hpp>
#include <usagi/tuple/has.hpp>

namespace usagi::tuple {
template <class TargetType, class TupleType> requires usagi::tuple::has_v<TargetType, TupleType>
inline constexpr decltype(auto) type_at(TupleType& tuple) noexcept {
  return std::get<usagi::tuple::get_index_v<TargetType, TupleType>>(tuple);
}
}
