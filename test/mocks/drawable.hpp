#pragma once

template <class ValueType, class DrawContextType>
struct Drawable {
  using value_type = ValueType;
  using draw_context_type = DrawContextType;
  void draw(draw_context_type &);
};

template <class ValueType, class DrawContextType>
struct UnDrawable {
  using value_type = ValueType;
  using draw_context_type = DrawContextType;
  // void draw(rect_type, draw_context_type &draw);
};
