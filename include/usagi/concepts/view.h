#pragma once

#include <usagi/geometry.h>
#ifdef __cpp_lib_concepts
#include <concepts>
#else
#include <usagi/legacy/concept_wrapper.h>
#endif

namespace usagi::concepts
{
#ifdef __cpp_lib_concepts
  template <class ViewType>
  concept view = requires(const ViewType &v)
  {
    typename ViewType::value_type;
    {
      v.width
    }
    ->std::floating_point;
    {
      v.height
    }
    ->std::floating_point;
    {
      v.affine
    }
    ->std::convertible_to<affine<typename ViewType::value_type>>;
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
  concept view = std::is_floating_point_v<typename ViewType::value_type> &&
      detail::has_width_v<ViewType> &&detail::has_height_v<ViewType> &&detail::has_affine_v<ViewType>;
#endif
}
