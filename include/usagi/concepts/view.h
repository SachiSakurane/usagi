#pragma once

#include <concepts>
#include <utility>

#include <usagi/geometry.h>

namespace usagi::concepts
{
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
}
