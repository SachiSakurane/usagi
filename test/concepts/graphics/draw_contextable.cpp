#include <gtest/gtest.h>
#include <usagi/concepts/graphics/draw_contextable.h>

#include "../../mocks/draw_contextable.h"

bool DrawContextableStaticTest()
{
  static_assert(usagi::concepts::graphics::draw_contextable<DrawContextable<float>>);
  static_assert(!usagi::concepts::graphics::draw_contextable<UnDrawContextable<float>>);

  return true;
}

TEST(DrawContextableConceptTest, StaticCase)
{
  ASSERT_TRUE(DrawContextableStaticTest());
}
