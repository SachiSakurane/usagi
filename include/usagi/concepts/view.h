#pragma once

#include <concepts>
#include <utility>

#include <usagi/concepts/app.h>

namespace usagi::concepts
{
  template <class ViewType>
  concept view = usagi::concepts::app<ViewType> && requires()
  {
    typename ViewType::value_type;
    typename ViewType::rect_type;
    typename ViewType::affine_type;

    { std::declval<std::add_const_t<ViewType>>().frame() } -> std::same_as<typename ViewType::rect_type>;
    { std::declval<std::add_const_t<ViewType>>().transform() } ->std::same_as<typename ViewType::affine_type>;
  };
}
