#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.h>
#include <usagi/geometry/rect/rect.h>
#include <usagi/geometry/size/size.h>

template <class ValueType>
struct Viewable
{
  using value_type = ValueType;
  using size_type = typename usagi::geometry::size<value_type>;
  using rect_type = typename usagi::geometry::rect<value_type>;
  size_type bounds() const;
  rect_type frame() const;
};

template <class ValueType>
struct UnViewable
{
  using value_type = ValueType;
  using size_type = typename usagi::geometry::size<value_type>;
  using rect_type = typename usagi::geometry::rect<value_type>;
  value_type bounds() const;
  rect_type frame() const;
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
