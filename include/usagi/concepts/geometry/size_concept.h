#pragma once

#include <utility>

#include <usagi/utility/convertible_to.h>

namespace usagi::concepts::geometry
{
  /** 
   * sizeが表現可能
  */
  template <class SizeType>
  concept size_concept = requires(SizeType &s)
  {
    typename SizeType::value_type;

    { s.width() } -> usagi::utility::convertible_to<typename SizeType::value_type>;
    { s.height() } -> usagi::utility::convertible_to<typename SizeType::value_type>;
    // { s() } -> usagi::utility::convertible_to<std::tuple<typename SizeType::value_type, typename SizeType::value_type>>;
  };
}
