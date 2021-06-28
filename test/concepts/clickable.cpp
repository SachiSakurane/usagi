#include <gtest/gtest.h>
#include <usagi/concepts/clickable.h>

template <class ValueType>
struct Clickable
{
  using value_type = ValueType;
  using mouse_traits = typename usagi::type::mouse::mouse_traits<value_type>;
  void event(typename mouse_traits::on_down);
  void event(typename mouse_traits::on_drag);
  void event(typename mouse_traits::on_up);
  void event(typename mouse_traits::on_over);
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
