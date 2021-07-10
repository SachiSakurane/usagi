#pragma once

#include <functional>

struct Draw {};

struct DrawContextable {
  using draw_type = float;
  void draw(draw_type &&d) const;
};

struct UnDrawContextable {
  using draw_type = std::function<void()>;
  void draw() const;
};
