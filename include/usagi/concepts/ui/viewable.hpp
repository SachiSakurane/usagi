#pragma once

#include <concepts>
#include <utility>

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/concepts/geometry/size_concept.hpp>
#include <usagi/concepts/ui/drawable.hpp>
#include <usagi/concepts/ui/gestural.hpp>

namespace usagi::ui {
/// Forward declaration for the owning UI view handle.
template <usagi::concepts::arithmetic ValueType, class DrawContextType, class GestureParameterType>
class view;
}

namespace usagi::concepts::ui {
/// Matches enabled view-like types that are both drawable and gestural.
///
/// @tparam ViewType Type to test.
template <class ViewType>
concept viewable = requires(ViewType &v) {
  requires usagi::concepts::ui::gestural<ViewType>;
  requires usagi::concepts::ui::drawable<ViewType>;

  { v.bounds() } -> usagi::concepts::geometry::size_concept;
  { v.frame() } -> usagi::concepts::geometry::rect_concept;

  v.set_enabled(std::declval<bool>());
  { v.is_enabled() } -> std::same_as<bool>;
};
} // namespace usagi::concepts::ui
