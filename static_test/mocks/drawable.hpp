#pragma once

#include <usagi/geometry/point.hpp>

template <class ValueType, class DrawContextType>
struct Drawable {
  using value_type = ValueType;
  using draw_context_type = DrawContextType;
  using offset_type = usagi::geometry::point<value_type>;
  void draw(draw_context_type &, offset_type);
};

template <class ValueType, class DrawContextType>
struct UnDrawable {
  using value_type = ValueType;
  using draw_context_type = DrawContextType;
  using offset_type = usagi::geometry::point<value_type>;
  // void draw(rect_type, draw_context_type &draw);
};
