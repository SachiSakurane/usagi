#pragma once

#include <functional>

namespace usagi::wrapper::icontrol {
template <class GraphicsType>
class draw_context {
public:
  using draw_type = std::function<void(GraphicsType &)>;

  draw_context(GraphicsType &g) : graphics{g} {}

  void draw(draw_type &&func) { std::forward<draw_type>(func)(graphics); }

private:
  GraphicsType &graphics;
};
} // namespace usagi::wrapper::icontrol
