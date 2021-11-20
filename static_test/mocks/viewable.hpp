#pragma once

#include <utility>

#include <usagi/concepts/arithmetic.hpp>
#include <usagi/ui/view.hpp>

#include "draw_context.hpp"
#include "drawable.hpp"
#include "gestural.hpp"

template <usagi::concepts::arithmetic ValueType>
struct Viewable : Gestural<ValueType>, Drawable<ValueType, DrawContext> {
  using value_type = ValueType;
  using size_type = typename usagi::geometry::size<value_type>;
  using rect_type = typename usagi::geometry::rect<value_type>;
  using draw_context_type = typename Drawable<ValueType, DrawContext>::draw_context_type;
  using gesture_parameter_type = typename Gestural<ValueType>::gesture_parameter_type;
  using view_type = usagi::ui::view<value_type, draw_context_type, gesture_parameter_type>;

  size_type bounds() const;
  rect_type frame() const;
  void set_enabled(bool flag);
  bool is_enabled() const;
};

template <usagi::concepts::arithmetic ValueType>
struct UnViewable : Gestural<ValueType>, Drawable<ValueType, DrawContext> {
  using value_type = ValueType;
  using size_type = typename usagi::geometry::size<value_type>;
  using rect_type = typename usagi::geometry::rect<value_type>;
  using draw_context_type = typename Drawable<ValueType, DrawContext>::draw_context_type;
  using gesture_parameter_type = typename Gestural<ValueType>::gesture_parameter_type;
  using view_type = usagi::ui::view<value_type, draw_context_type, gesture_parameter_type>;
  size_type bounds() const;
  rect_type frame() const;
  view_type &add_sub_view(view_type &&);
  // bool remove_sub_view(size_t);
  size_t sub_view_size() const;
};
