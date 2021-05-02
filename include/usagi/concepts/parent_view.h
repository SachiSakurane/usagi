#pragma once

#include <usagi/concepts/view.h>

namespace usagi::concepts
{
#ifdef __cpp_lib_concepts
  template <usagi::concepts::view ParentViewType, usagi::concepts::view... ChildViewType>
  concept parent_view = requires()
  {
    {
      std::declval<ParentViewType>().children()
    }
    ->std::convertible_to<std::tuple<ChildViewType...>>;
  };
#else
#endif
}
