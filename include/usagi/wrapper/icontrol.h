#pragma once

namespace usagi::wrapper
{
  // viewを持つ
  template <class IControlType>
  class icontrol : public IControlType
  {
  public:
    icontrol(const IRECT &bounds) : IControlType{bounds} {}

    void Draw(IGraphics &g) override
    {
    }

    void OnMouseDown(float x, float y, const IMouseMod &mod) override
    {
    }

    void OnMouseDrag(float x, float y, float dX, float dY, const IMouseMod &mod) override
    {
    }

    void OnMouseUp(float x, float y, const IMouseMod &mod) override
    {
    }

    void OnMouseOver(float x, float y, const IMouseMod &mod) override
    {
    }

  private:
  };
}
