#pragma once

#include <concepts>
#include <utility>

namespace usagi::concepts
{
  /** 
   * concepts は内部で決定されるべき(関係は関係として別の concepts になりうる)
  */
  template <class AppType>
  concept app = requires()
  {
    typename AppType::value_type;
    typename AppType::size_type;

    { std::declval<std::add_const_t<AppType>>().bounds() } -> std::same_as<typename AppType::size_type>;
  };
}
