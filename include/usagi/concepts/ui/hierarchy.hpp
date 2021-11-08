#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>

#include <usagi/utility/convertible_to.hpp>

namespace usagi::concepts::ui {
/**
 * 親子関係を持っているか
 */
template <class HierarchyType>
concept hierarchy = requires(HierarchyType &h) {
  typename HierarchyType::children_key_type;
  typename HierarchyType::children_mapped_type;
  typename HierarchyType::children_value_type;

  {
    h.add_sub_view(std::declval<typename HierarchyType::children_mapped_type>())
    } -> usagi::utility::convertible_to<
        std::add_lvalue_reference_t<typename HierarchyType::children_value_type>>;

  {
    h.get_sub_view(std::declval<typename HierarchyType::children_key_type>())
    } -> usagi::utility::convertible_to<
        std::add_lvalue_reference_t<typename HierarchyType::children_mapped_type>>;

  {
    h.remove_sub_view(std::declval<typename HierarchyType::children_key_type>())
    } -> std::same_as<bool>;

  { h.sub_view_size() } -> std::same_as<size_t>;
};
} // namespace usagi::concepts::ui
