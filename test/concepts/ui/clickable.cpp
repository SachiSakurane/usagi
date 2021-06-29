#include <gtest/gtest.h>
#include <usagi/concepts/ui/clickable.h>

#include "../../mocks/clickable.h"

bool ClickableStaticTest()
{
  static_assert(usagi::concepts::ui::clickable<Clickable<int>>);
  static_assert(!usagi::concepts::ui::clickable<UnClickable<int>>);

  return true;
}

TEST(ClickableTest, StaticCase)
{
  ASSERT_TRUE(ClickableStaticTest());
}
