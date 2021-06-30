#pragma once

#include <usagi/ui/view.h>
#include <usagi/utility/arithmetic.h>

#include "clickable.h"
#include "draw_contextable.h"
#include "drawable.h"

template <usagi::utility::arithmetic ValueType>
struct Viewable : Clickable<ValueType>, Drawable<ValueType, DrawContextable<ValueType>>
{
  using value_type = ValueType;
  using size_type = typename usagi::geometry::size<value_type>;
  using rect_type = typename usagi::geometry::rect<value_type>;
  using draw_context_type = typename Drawable<ValueType, DrawContextable<ValueType>>::draw_context_type;
  using view_type = usagi::ui::view<value_type, draw_context_type>;
  size_type bounds() const;
  rect_type frame() const;
  view_type &add_sub_view(view_type &&);
};

template <usagi::utility::arithmetic ValueType>
struct UnViewable : Clickable<ValueType>, Drawable<ValueType, DrawContextable<ValueType>>
{
  using value_type = ValueType;
  using size_type = typename usagi::geometry::size<value_type>;
  using rect_type = typename usagi::geometry::rect<value_type>;
  using draw_context_type = typename Drawable<ValueType, DrawContextable<ValueType>>::draw_context_type;
  using view_type = usagi::ui::view<value_type, draw_context_type>;
  // size_type bounds() const;
  rect_type frame() const;
  view_type &add_sub_view(view_type &&);
};
