#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.h>
#include <usagi/ui/view.h>

#include "../mocks/viewable.h"

bool ViewStaticTest()
{
  static_assert(usagi::concepts::ui::viewable<usagi::ui::view<float, DrawContextable<float>>>);
  static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{std::declval<Viewable<float>>()})>);
  static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{(std::declval<Viewable<float>>())})>);

  return true;
}

TEST(ViewTest, StaticCase)
{
  ASSERT_TRUE(ViewStaticTest);
}
