#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/concepts/ui/clickable.hpp>
#include <usagi/concepts/ui/drawable.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::ui {
template <usagi::utility::arithmetic ValueType, class DrawContextType>
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
concept viewable = usagi::concepts::geometry::size_concept<typename ViewType::size_type> &&
    usagi::concepts::geometry::rect_concept<typename ViewType::rect_type> &&
    usagi::concepts::ui::clickable<ViewType> && usagi::concepts::ui::drawable<ViewType> &&
    requires(ViewType &v) {
  typename ViewType::value_type;
  typename ViewType::draw_context_type;

  { v.bounds() } -> usagi::concepts::geometry::size_concept;
  { v.frame() } -> usagi::concepts::geometry::rect_concept;

  {
    v.add_sub_view(
        std::declval<
            usagi::ui::view<typename ViewType::value_type, typename ViewType::draw_context_type>>())
    } -> std::same_as<std::add_lvalue_reference_t<
        usagi::ui::view<typename ViewType::value_type, typename ViewType::draw_context_type>>>;
};
} // namespace usagi::concepts::ui
