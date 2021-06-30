#pragma once

#include <usagi/concepts/geometry/rect_concept.h>
#include <usagi/concepts/geometry/size_concept.h>
#include <usagi/concepts/graphics/color_concept.h>
#include <usagi/geometry/size/size.h>
#include <usagi/utility/arithmetic.h>

namespace usagi::wrapper::icontrol
{
  template <usagi::utility::arithmetic ValueType, class GraphicsType>
  class draw_context
  {
  public:
    draw_context(GraphicsType &g) : graphics{g} {}

    ValueType width() const { return static_cast<ValueType>(graphics.Width()); }
    ValueType height() const { return static_cast<ValueType>(graphics.Height()); }

    void fill(const usagi::concepts::geometry::rect_concept auto &rect, const usagi::concepts::graphics::color_concept auto &color)
    {
      SkCanvas *canvas = static_cast<SkCanvas *>(graphics.GetDrawContext());
    }

  private:
    GraphicsType &graphics;
  };
}
