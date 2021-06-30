#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.h>

#include "../../mocks/viewable.h"

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
