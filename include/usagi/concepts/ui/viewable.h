#pragma once

#include <type_traits>
#include <utility>

#include <usagi/concepts/geometry/rect_concept.h>
#include <usagi/concepts/geometry/size_concept.h>
#include <usagi/utility/convertible_to.h>

namespace usagi::concepts::ui
{
  /** 
   * view を表現可能
   * TODO: affine の必要性について考える(view として持つ必要性がなさそうに思える)
  */
  template <class ViewType>
  concept viewable =
      usagi::concepts::geometry::size_concept<typename ViewType::size_type> &&
      usagi::concepts::geometry::rect_concept<typename ViewType::rect_type> &&
      requires(ViewType &v)
  {
    typename ViewType::value_type;
    typename ViewType::size_type;
    typename ViewType::rect_type;

    { v.bounds() } -> usagi::utility::convertible_to<typename ViewType::size_type>;
    { v.frame() } -> usagi::utility::convertible_to<typename ViewType::rect_type>;
    // { v.affine() } -> usagi::utility::convertible_to<typename ViewType::affine_type>;
  };
}
