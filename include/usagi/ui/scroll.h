#pragma once

#include <usagi/geometry/rect.h>

namespace usagi::components
{
  // centering
  // horizontal
  template <class FrameType, class ViewType>
  class scroll
  {
    static constexpr float SCROLL_DISTANCE = 12.f;

  public:
    scroll(const FrameType &frame, ViewType &&content_view) : frame{frame}, content{content_view}
    {
    }

    void draw(IGraphics &g)
    {
      content.draw(g, frame.bounds() + offset);
    }

    void on_down(const point<float> &p)
    {
      if (contain(frame.bounds(), p))
      {
        start_point = p;
        is_scroll = false;
        content.on_down(p);
      }
    }

    void on_drag(const point<float> &p)
    {
      if (is_scroll)
      {
        offset = p - scroll_start;
        content.on_drag(p);
      }
      else if (!is_scroll && distance(start_point, p) > SCROLL_DISTANCE)
      {
        is_scroll = true;
        scroll_start = p;
        content.on_cancel(p);
      }
    }

    void on_up(const point<float> &p)
    {
      if (!is_scroll)
      {
        content.on_up(p);
      }
    }

    void on_cancel(const point<float> &p)
    {
      is_scroll = false;
      content.on_cancel(p);
    }

  private:
    const FrameType &frame;
    ViewType content;
    point<float> start_point, scroll_start;
    point<float> offset{0, 0};
    bool is_scroll{false};
  };

  template <class FrameType, class ViewType>
  scroll(const FrameType, ViewType &) -> scroll<FrameType, ViewType>;
}
