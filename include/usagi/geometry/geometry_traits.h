#pragma once

#include <usagi/geometry/point/point.h>
#include <usagi/geometry/rect/rect.h>
#include <usagi/geometry/size/size.h>
#include <usagi/utility/arithmetic.h>

namespace usagi::geometry
{
  template <usagi::utility::arithmetic ValueType>
  struct geometry_traits
  {
    using value_type = ValueType;
    using point_type = typename usagi::geometry::point<value_type>;
    using rect_type = typename usagi::geometry::rect<value_type>;
    using size_type = typename usagi::geometry::size<value_type>;
  };
}
