#pragma once

#include <usagi/variable/variable.hpp>

namespace usagi {
/// Maps a value type to its variable wrapper type.
///
/// @tparam ValueType Value produced by the variable wrapper.
template <class ValueType>
struct variable_traits {
  /// Produced value type.
  using value_type = ValueType;
  /// Variable wrapper type for `value_type`.
  using variable_type = usagi::variable<value_type>;
};
} // namespace usagi
