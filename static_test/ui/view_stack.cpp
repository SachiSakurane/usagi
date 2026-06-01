#include <usagi/concepts/ui/view_container.hpp>
#include <usagi/ui/view_stack.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_parameter<float>;
using ViewStack = usagi::ui::view_stack<float, DrawContext, GestureParameterType>;

struct ChildContainerOnly {
  using child_view_key_type = size_t;
  using child_view_type = usagi::ui::view<float, DrawContext, GestureParameterType>;

  child_view_key_type add_child_view(child_view_type &&);
  child_view_type &get_child_view(child_view_key_type);
  bool remove_child_view(child_view_key_type);
  size_t child_view_size() const;
};

static_assert(usagi::concepts::ui::view_container<ViewStack>);
static_assert(usagi::concepts::ui::viewable<ViewStack>);
static_assert(!usagi::concepts::ui::view_container<ChildContainerOnly>);
} // namespace
