#include <usagi/concepts/ui/gestural.hpp>

#include "../../mocks/gestural.hpp"

namespace {
static_assert(usagi::concepts::ui::gestural<Gestural<float>>);
static_assert(!usagi::concepts::ui::gestural<UnGestural<float>>);
} // namespace
