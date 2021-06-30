#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.h>
#include <usagi/geometry/rect/rect.h>
#include <usagi/geometry/size/size.h>

#include "../../mocks/clickable.h"
#include "../../mocks/drawable.h"
#include "../../mocks/draw_contextable.h"

template <class ValueType>
struct Viewable : Clickable<ValueType>, Drawable<ValueType, DrawContextable>
{
  using value_type = ValueType;
  using size_type = typename usagi::geometry::size<value_type>;
  using rect_type = typename usagi::geometry::rect<value_type>;
  using draw_context_type = typename Drawable<ValueType, DrawContextable>::draw_context_type;
  using view_type = usagi::ui::view<value_type, draw_context_type>;
  size_type bounds() const;
  rect_type frame() const;
  void add_sub_view(view_type&&);
};

template <class ValueType>
struct UnViewable : Clickable<ValueType>, Drawable<ValueType, DrawContextable>
{
  using value_type = ValueType;
  using size_type = typename usagi::geometry::size<value_type>;
  using rect_type = typename usagi::geometry::rect<value_type>;
  using draw_context_type = typename Drawable<ValueType, DrawContextable>::draw_context_type;
  using view_type = usagi::ui::view<value_type, draw_context_type>;
  // size_type bounds() const;
  rect_type frame() const;
  void add_sub_view(view_type &&);
};

bool ViewableStaticTest()
{
  static_assert(usagi::concepts::ui::viewable<Viewable<int>>);
  static_assert(!usagi::concepts::ui::viewable<UnViewable<int>>);

  return true;
}

TEST(ViewableTest, StaticCase)
{
  ASSERT_TRUE(ViewableStaticTest());
}
