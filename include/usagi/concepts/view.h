#pragma once

#include <usagi/geometry.h>
#ifndef __cpp_lib_concepts
#include <usagi/legacy/concept_wrapper.h>
#endif

namespace usagi::concepts
{
#ifdef __cpp_lib_concepts
  concept view = requires()
  {
    typename ViewType::value_type;
    std::enable_if_t<std::is_arithmetic_v<typename ViewType::value_type>>();
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
    USAGI_CONCEPT(has_affine,
                  (std::is_same_v<affine<typename Type::value_type>, decltype(std::declval<Type>().affine)>))
  }

  template <class ViewType>
  concept view = std::is_arithmetic_v<typename ViewType::value_type> &&
      detail::has_width_v<ViewType> && detail::has_height_v<ViewType> && detail::has_affine_v<ViewType>;
#endif
}
