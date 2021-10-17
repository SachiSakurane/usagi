#pragma once

#include <utility>

#include <usagi/ui/view.hpp>
#include <usagi/utility/arithmetic.hpp>

#include "clickable.hpp"
#include "draw_context.hpp"
#include "drawable.hpp"

template <usagi::utility::arithmetic ValueType>
struct Viewable : Clickable<ValueType>, Drawable<ValueType, DrawContext> {
  using value_type = ValueType;
  using size_type = typename usagi::geometry::size<value_type>;
  using rect_type = typename usagi::geometry::rect<value_type>;
  using draw_context_type = typename Drawable<ValueType, DrawContext>::draw_context_type;
  using mouse_parameter_type = typename Clickable<ValueType>::mouse_parameter_type;
  using view_type = usagi::ui::view<value_type, draw_context_type, mouse_parameter_type>;

  using children_type = std::map<view_type, size_t>;
  using children_key_type = typename children_type::key_type;
  using children_mapped_type = typename children_type::mapped_type;
  using children_value_type = typename children_type::value_type;

  size_type bounds() const;
  rect_type frame() const;
  children_value_type &add_sub_view(children_mapped_type &&);
  children_mapped_type &get_sub_view(children_key_type);
  bool remove_sub_view(children_key_type);
  size_t sub_view_size() const;
  void set_enabled(bool flag);
  bool is_enabled() const;
};

template <usagi::utility::arithmetic ValueType>
struct UnViewable : Clickable<ValueType>, Drawable<ValueType, DrawContext> {
  using value_type = ValueType;
  using size_type = typename usagi::geometry::size<value_type>;
  using rect_type = typename usagi::geometry::rect<value_type>;
  using draw_context_type = typename Drawable<ValueType, DrawContext>::draw_context_type;
  using mouse_parameter_type = typename Clickable<ValueType>::mouse_parameter_type;
  using view_type = usagi::ui::view<value_type, draw_context_type, mouse_parameter_type>;
  size_type bounds() const;
  rect_type frame() const;
  view_type &add_sub_view(view_type &&);
  // bool remove_sub_view(size_t);
  size_t sub_view_size() const;
};
