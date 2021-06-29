#include <gtest/gtest.h>
#include <usagi/concepts/graphics/color_concept.h>
#include <usagi/concepts/ui/drawable.h>

template <class DrawContextType>
struct Drawable
{
  using draw_context_type = DrawContextType;
  void draw(draw_context_type &draw);
};

template <class DrawContextType>
struct UnDrawable
{
  using draw_context_type = DrawContextType;
  // void draw(draw_context_type &draw);
};

struct DrawContext
{
  void fill(const usagi::concepts::graphics::color_concept auto &) const;
};

bool DrawableStaticTest()
{
  static_assert(usagi::concepts::ui::drawable<Drawable<DrawContext>>);
  static_assert(!usagi::concepts::ui::drawable<UnDrawable<DrawContext>>);

  return true;
}

TEST(DrawableTest, StaticCase)
{
  ASSERT_TRUE(DrawableStaticTest());
}
