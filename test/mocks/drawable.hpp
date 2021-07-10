#pragma once

#include <usagi/concepts/graphics/draw_contextable.hpp>
#include <usagi/geometry/rect/rect.hpp>

template <class ValueType, usagi::concepts::graphics::draw_contextable DrawContextType>
struct Drawable {
  using value_type = ValueType;
  using draw_context_type = DrawContextType;
  using rect_type = usagi::geometry::rect<value_type>;
  void draw(draw_context_type &);
};

template <class ValueType, usagi::concepts::graphics::draw_contextable DrawContextType>
struct UnDrawable {
  using value_type = ValueType;
  using draw_context_type = DrawContextType;
  using rect_type = usagi::geometry::rect<value_type>;
  // void draw(rect_type, draw_context_type &draw);
};
