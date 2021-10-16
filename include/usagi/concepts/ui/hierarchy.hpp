#pragma once

#include <type_traits>

#include <usagi/utility/convertible_to.hpp>

namespace usagi::concepts::ui {
/**
 * 親子関係を持っているか
 */
template <class HierarchyType>
concept hierarchy = requires(HierarchyType &h) {
  typename HierarchyType::view_type;

  {
    h.add_sub_view(std::declval<typename HierarchyType::view_type>())
    } -> usagi::utility::convertible_to<
        std::add_lvalue_reference_t<typename HierarchyType::view_type>>;

  {
    h.get_sub_view(std::declval<std::size_t>())
    } -> usagi::utility::convertible_to<
        std::add_lvalue_reference_t<typename HierarchyType::view_type>>;

  { h.remove_sub_view(std::declval<std::size_t>()) } -> std::same_as<bool>;
  { h.sub_view_size() } -> std::same_as<std::size_t>;
};
} // namespace usagi::concepts::ui
