#pragma once

#include <usagi/geometry/rect/rect.h>

template <class ValueType, class DrawContextType>
struct Drawable
{
  using value_type = ValueType;
  using draw_context_type = DrawContextType;
  using rect_type = usagi::geometry::rect<value_type>;
  void draw(rect_type, draw_context_type &);
};

template <class ValueType, class DrawContextType>
struct UnDrawable
{
  using value_type = ValueType;
  using draw_context_type = DrawContextType;
  using rect_type = usagi::geometry::rect<value_type>;
  // void draw(rect_type, draw_context_type &draw);
};
