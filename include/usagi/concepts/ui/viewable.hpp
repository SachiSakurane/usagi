#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/convertible_to.hpp>
#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/concepts/ui/drawable.hpp>
#include <usagi/concepts/ui/gestural.hpp>
#include <usagi/concepts/ui/hierarchy.hpp>
#include <usagi/type/mouse.hpp>

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
concept viewable = requires(ViewType &v) {
  requires usagi::concepts::ui::gestural<ViewType>;
  requires usagi::concepts::ui::drawable<ViewType>;
  requires usagi::concepts::ui::hierarchy<ViewType>;

  { v.bounds() } -> usagi::concepts::geometry::size_concept;
  { v.frame() } -> usagi::concepts::geometry::rect_concept;

  v.set_enabled(std::declval<bool>());
  { v.is_enabled() } -> std::same_as<bool>;
};
} // namespace usagi::concepts::ui
