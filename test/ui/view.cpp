#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/ui/view.hpp>

#include "../mocks/viewable.hpp"

namespace
{
  static_assert(usagi::concepts::ui::viewable<usagi::ui::view<float, DrawContextable<float>>>);
  static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{std::declval<Viewable<float>>()})>);
  static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{(std::declval<Viewable<float>>())})>);
}
