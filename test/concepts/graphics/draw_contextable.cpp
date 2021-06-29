#include <gtest/gtest.h>
#include <usagi/concepts/graphics/color_concept.h>
#include <usagi/concepts/graphics/draw_contextable.h>

struct DrawContextable
{
  void fill(const usagi::concepts::graphics::color_concept auto &) const;
};

struct UnDrawContextable
{
  void fill() const;
};

bool DrawContextableStaticTest()
{
  static_assert(usagi::concepts::graphics::draw_contextable<DrawContextable>);
  static_assert(!usagi::concepts::graphics::draw_contextable<UnDrawContextable>);

  return true;
}

TEST(DrawContextableConceptTest, StaticCase)
{
  ASSERT_TRUE(DrawContextableStaticTest());
}
