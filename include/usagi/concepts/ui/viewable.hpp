#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/concepts/ui/clickable.hpp>
#include <usagi/concepts/ui/drawable.hpp>
#include <usagi/type/mouse.hpp>
#include <usagi/utility/arithmetic.hpp>
#include <usagi/utility/convertible_to.hpp>

namespace usagi::ui {
template <usagi::utility::arithmetic ValueType, class DrawContextType, class MouseParameterType>
class view;
}

namespace usagi::concepts::ui {
/**
 * view を表現可能かどうか
 *
 * view は大きさを表現できる
 * view は親子関係を表現できる
 * view は drawable
 * view は clickable
 * TODO: affine の必要性について考える(view として持つ必要性がなさそうに思える)
 */
template <class ViewType>
concept viewable = usagi::concepts::ui::clickable<ViewType> &&
    usagi::concepts::ui::drawable<ViewType> && requires(ViewType &v) {
  typename ViewType::view_type;

  { v.bounds() } -> usagi::concepts::geometry::size_concept;
  { v.frame() } -> usagi::concepts::geometry::rect_concept;

  {
    v.add_sub_view(std::declval<typename ViewType::view_type>())
    } -> usagi::utility::convertible_to<std::add_lvalue_reference_t<typename ViewType::view_type>>;

  { v.remove_sub_view(std::declval<std::size_t>()) } -> std::same_as<bool>;
  { v.sub_view_size() } -> std::same_as<std::size_t>;
};
} // namespace usagi::concepts::ui
