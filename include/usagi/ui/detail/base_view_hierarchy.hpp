#pragma once

#include <iterator>
#include <map>

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/concepts/ui/hierarchy.hpp>

namespace usagi::ui::detail {
template <class ViewType, class KeyType = size_t>
class base_view_hierarchy {
public:
  using children_mapped_type = ViewType;
  using children_key_type = KeyType;
  using children_type = std::map<children_key_type, children_mapped_type>;
  using children_value_type = typename children_type::value_type;

  children_value_type &add_sub_view(children_mapped_type &&sub_view) {
    const auto current_index = children_next_index;
    children_next_index += 1;
    return *children.try_emplace(std::end(children), current_index,
                                 std::forward<children_mapped_type>(sub_view));
  }

  children_mapped_type &get_sub_view(children_key_type index) {
    assert(children.find(index) != std::end(children));
    return children.at(index);
  }

  bool remove_sub_view(children_key_type index) {
    if (auto it = children.find(index); it != std::end(children)) {
      children.erase(it);
      return true;
    }
    return false;
  }

  [[nodiscard]] size_t sub_view_size() const { return children.size(); }

  children_type &get_children() & { return children; }

private:
  size_t children_next_index{0};
  children_type children;
};

} // namespace usagi::ui::detail
