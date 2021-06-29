#pragma once

#include <type_traits>
#include <utility>

#include <usagi/utility/convertible_to.h>

namespace usagi::concepts::ui
{
  /** 
   * content が表現可能
   * content は二次元で表現される箱みたいなもの
  */
  template <class ContentType>
  concept contentable = requires()
  {
    typename ContentType::value_type;
    typename ContentType::size_type;

    { std::declval<std::add_const_t<ContentType>>().bounds() } -> usagi::utility::convertible_to<typename ContentType::size_type>;
  };
}
