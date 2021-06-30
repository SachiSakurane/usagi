#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.h>
#include <usagi/ui/view.h>

#include "../mocks/draw_contextable.h"

bool ViewStaticTest()
{
  static_assert(usagi::concepts::ui::viewable<usagi::ui::view<float, DrawContextable>>);

  return true;
}

TEST(ViewTest, StaticCase)
{
  ASSERT_TRUE(ViewStaticTest);
}
