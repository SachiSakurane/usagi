#pragma once

#include <usagi/concepts/view.h>

namespace usagi::concepts
{
  template <usagi::concepts::view ParentViewType>
  concept parent_view = requires(){
      std::declval<ParentViewType>().children()
  };
}
