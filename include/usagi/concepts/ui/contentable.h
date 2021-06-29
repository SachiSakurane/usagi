#pragma once

#include <type_traits>
#include <utility>

#include <usagi/utility/convertible_to.h>

namespace usagi::concepts::ui
{
  /** 
   * contentが表現可能
  */
  template <class ContentType>
  concept contentable = requires()
  {
    typename ContentType::value_type;
    typename ContentType::size_type;

    { std::declval<std::add_const_t<ContentType>>().bounds() } -> usagi::utility::convertible_to<typename ContentType::size_type>;
  };
}
