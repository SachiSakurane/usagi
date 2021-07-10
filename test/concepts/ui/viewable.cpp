#include <usagi/concepts/ui/viewable.hpp>

#include "../../mocks/viewable.hpp"

namespace {
static_assert(usagi::concepts::ui::viewable<Viewable<int>>);
static_assert(!usagi::concepts::ui::viewable<UnViewable<int>>);
} // namespace
