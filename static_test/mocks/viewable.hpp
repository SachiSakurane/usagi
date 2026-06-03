#pragma once

#include <utility>

#include <usagi/concepts/floating_point.hpp>
#include <usagi/ui/view.hpp>

#include "draw_context.hpp"
#include "drawable.hpp"
#include "gestural.hpp"

template <usagi::concepts::floating_point ValueType>
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

template <usagi::concepts::floating_point ValueType>
struct UnViewable : Gestural<ValueType>, Drawable<ValueType, DrawContext> {
  using value_type = ValueType;
  using size_type = typename usagi::geometry::size<value_type>;
  using rect_type = typename usagi::geometry::rect<value_type>;
  using draw_context_type = typename Drawable<ValueType, DrawContext>::draw_context_type;
  using gesture_parameter_type = typename Gestural<ValueType>::gesture_parameter_type;
  using view_type = usagi::ui::view<value_type, draw_context_type, gesture_parameter_type>;
  size_type bounds() const;
  rect_type frame() const;
  size_t add_child_view(view_type &&);
  // bool remove_child_view(size_t);
  size_t child_view_size() const;
};
