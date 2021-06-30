#include <usagi/concepts/ui/clickable.h>

#include "../../mocks/clickable.h"

namespace
{
  static_assert(usagi::concepts::ui::clickable<Clickable<int>>);
  static_assert(!usagi::concepts::ui::clickable<UnClickable<int>>);
}
