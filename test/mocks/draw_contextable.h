#pragma once

#include <usagi/concepts/graphics/color_concept.h>

struct DrawContextable
{
  void fill(const usagi::concepts::graphics::color_concept auto &) const;
};

struct UnDrawContextable
{
  void fill() const;
};
