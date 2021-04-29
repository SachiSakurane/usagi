#pragma once

#include "IControl.h"
#include "SkImageFilters.h"

namespace udon::effects
{
  template <class FrameType>
  class color_blur
  {
  public:
    color_blur(SkColor4f color, FrameType &view) : color{color}, view{view}
    {
      paint.setColor4f(color);
      effect.setImageFilter(SkImageFilters::Blur(2, 2, SkTileMode::kDecal, nullptr));
      effect.setAntiAlias(true);
    }

    void draw(IGraphics &g)
    {
      auto bounds = view.bounds();
      SkCanvas *canvas = static_cast<SkCanvas *>(g.GetDrawContext());
      auto skirect = SkIRect::MakeXYWH(bounds.l(), bounds.t(), bounds.width(), bounds.height());
      canvas->drawRect(SkRect::Make(skirect), paint);
      canvas->drawImage(canvas->getSurface()->makeImageSnapshot(skirect), bounds.l(), bounds.t(), &effect);
    }

  private:
    FrameType &view;
    SkColor4f color;
    SkPaint paint, effect;
  };
}
