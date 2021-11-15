#include <usagi/ui/detail/base_view_hierarchy.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext {};
using MouseParameter = usagi::type::gesture_default_parameter<float>;
using ViewType = usagi::ui::base_view<float, DrawContext, MouseParameter>;

static_assert(usagi::concepts::ui::hierarchy<usagi::ui::detail::base_view_hierarchy<ViewType>>);
}
