#pragma once

#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/concepts/graphics/color_concept.hpp>
#include <usagi/utility/arithmetic.hpp>

template <usagi::utility::arithmetic ValueType>
struct DrawContextable
{
  ValueType width() const;
  ValueType height() const;
  void fill(const usagi::concepts::geometry::rect_concept auto &, const usagi::concepts::graphics::color_concept auto &) const;
};

template <usagi::utility::arithmetic ValueType>
struct UnDrawContextable
{
  ValueType width() const;
  ValueType height() const;
  void fill() const;
};
