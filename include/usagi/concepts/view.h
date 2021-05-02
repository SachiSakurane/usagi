#pragma once

#include <usagi/geometry.h>
#ifndef __cpp_lib_concepts
#include <usagi/legacy/concept_wrapper.h>
#endif

namespace usagi
{
#ifdef __cpp_lib_concepts
  concept view = requires()
  {
    typename ViewType::value_type;
    {
      std::declval<ViewType>().width
    }
    ->value_type;
    {
      std::declval<ViewType>().height
    }
    ->value_type;
    {
      std::declval<ViewType>().affine
    }
    ->affine<value_type>;
  };
#else
  namespace detail
  {
    USAGI_CONCEPT(has_width,
                  (std::is_same_v<typename Type::value_type, decltype(std::declval<Type>().width)>))
    USAGI_CONCEPT(has_height,
                  (std::is_same_v<typename Type::value_type, decltype(std::declval<Type>().height)>))
  }
#endif
}
