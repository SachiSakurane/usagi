#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

#include <usagi/concepts/convertible_to.hpp>
#include <usagi/concepts/ui/viewable.hpp>

namespace usagi::concepts::ui {
/**
 * child view collection を持っているか
 */
template <class ContainerType>
concept view_container = usagi::concepts::ui::viewable<ContainerType> &&
                         requires(ContainerType &container) {
  typename ContainerType::child_view_key_type;
  typename ContainerType::child_view_type;

  {
    container.add_child_view(std::declval<typename ContainerType::child_view_type>())
    } -> std::same_as<typename ContainerType::child_view_key_type>;

  {
    container.get_child_view(std::declval<typename ContainerType::child_view_key_type>())
    } -> usagi::concepts::convertible_to<
        std::add_lvalue_reference_t<typename ContainerType::child_view_type>>;

  {
    container.remove_child_view(std::declval<typename ContainerType::child_view_key_type>())
    } -> std::same_as<bool>;

  { container.child_view_size() } -> std::same_as<size_t>;
};
} // namespace usagi::concepts::ui
