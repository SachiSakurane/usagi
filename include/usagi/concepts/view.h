#pragma once

#include <concepts>

namespace usagi
{
  template <class Type>
  concept event = requires()
  {
    typename Type::point_type;
    std::declval<Type>().on_down(std::declval<Type::point_type>());
    std::declval<Type>().on_drag(std::declval<Type::point_type>());
    std::declval<Type>().on_up(std::declval<Type::point_type>());
    std::declval<Type>().on_cancel(std::declval<Type::point_type>());
  };

  template <class Type>
  concept frame = requires()
  {
    typename Type::rect_type;
    {
      std::declval<std::add_const_t<Type>>().bounds()
    }
    ->std::same_as<typename Type::rect_type>;

    std::declval<Type>().set_bounds(std::declval<Type::rect_type>());
  };
}
