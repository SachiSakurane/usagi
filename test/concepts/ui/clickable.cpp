#include <usagi/concepts/ui/clickable.hpp>

#include "../../mocks/clickable.hpp"

namespace {
static_assert(usagi::concepts::ui::clickable<Clickable<int>>);
static_assert(!usagi::concepts::ui::clickable<UnClickable<int>>);
} // namespace
