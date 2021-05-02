#pragma once

#include <utility>

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
  concept view = requires()
  {
    typename ViewType::value_type;
    typename ViewType::affine_type;
    {
      std::declval<std::add_const_t<ViewType>>().width()
    }
    ->std::floating_point;
    {
      std::declval<std::add_const_t<ViewType>>().height()
    }
    ->std::floating_point;
    {
      std::declval<std::add_const_t<ViewType>>().transform()
    }
    ->std::convertible_to<typename ViewType::affine_type>;
  };
#else
  namespace detail
  {
    USAGI_CONCEPT(has_width,
                  (std::is_same_v<typename Type::value_type, decltype(std::declval<Type>().width())>))
    USAGI_CONCEPT(has_height,
                  (std::is_same_v<typename Type::value_type, decltype(std::declval<Type>().height())>))
    USAGI_CONCEPT(has_transform,
                  (std::is_same_v<affine<typename Type::value_type>, decltype(std::declval<Type>().transform())>))
  }

  template <class ViewType>
  concept view = std::is_floating_point_v<typename ViewType::value_type> &&
      detail::has_width<ViewType>::value &&detail::has_height<ViewType>::value &&detail::has_transform<ViewType>::value;
#endif
}
