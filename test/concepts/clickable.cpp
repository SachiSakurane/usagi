#include <gtest/gtest.h>
#include <usagi/concepts/clickable.h>

template <class ValueType>
struct Clickable
{
  using value_type = ValueType;
  using mouse_traits = typename usagi::type::mouse::mouse_traits<value_type>;
  void event(typename mouse_traits::on_down_type);
  void event(typename mouse_traits::on_drag_type);
  void event(typename mouse_traits::on_up_type);
  void event(typename mouse_traits::on_over_type);
};

bool ClickableStaticTest()
{
  static_assert(usagi::concepts::clickable<Clickable<int>>);

  return true;
}

TEST(ClickableTest, StaticCase)
{
  ASSERT_TRUE(ClickableStaticTest());
}
