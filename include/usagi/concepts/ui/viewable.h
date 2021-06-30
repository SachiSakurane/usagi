#pragma once

#include <type_traits>
#include <utility>

#include <usagi/concepts/geometry/rect_concept.h>
#include <usagi/concepts/geometry/size_concept.h>
#include <usagi/concepts/graphics/draw_contextable.h>
#include <usagi/concepts/ui/clickable.h>
#include <usagi/concepts/ui/drawable.h>
#include <usagi/utility/convertible_to.h>

namespace usagi::ui
{
  template <class ValueType, usagi::concepts::graphics::draw_contextable DrawContextType>
  class view;
}

namespace usagi::concepts::ui
{
  /** 
   * view を表現可能かどうか
   * view は大きさを表現できる
   * TODO: view は親子関係を表現できる
   * view は drawable
   * view は clickable
   * TODO: affine の必要性について考える(view として持つ必要性がなさそうに思える)
  */
  template <class ViewType>
  concept viewable =
      usagi::concepts::geometry::size_concept<typename ViewType::size_type> &&
      usagi::concepts::geometry::rect_concept<typename ViewType::rect_type> &&
      usagi::concepts::graphics::draw_contextable<typename ViewType::draw_context_type> &&
      usagi::concepts::ui::clickable<ViewType> &&
      usagi::concepts::ui::drawable<ViewType> &&
      requires(ViewType &v)
  {
    typename ViewType::value_type;
    typename ViewType::size_type;
    typename ViewType::rect_type;
    typename ViewType::draw_context_type;

    { v.bounds() } -> usagi::utility::convertible_to<typename ViewType::size_type>;
    { v.frame() } -> usagi::utility::convertible_to<typename ViewType::rect_type>;

    v.add_sub_view(std::declval<usagi::ui::view<typename ViewType::value_type, typename ViewType::draw_context_type>>());
    // { v.affine() } -> usagi::utility::convertible_to<typename ViewType::affine_type>;
  };
}