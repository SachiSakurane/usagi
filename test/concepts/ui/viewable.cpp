#include <usagi/concepts/ui/viewable.h>

#include "../../mocks/viewable.h"

namespace
{
  static_assert(usagi::concepts::ui::viewable<Viewable<int>>);
  static_assert(!usagi::concepts::ui::viewable<UnViewable<int>>);
}
