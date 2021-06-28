#include <gtest/gtest.h>
#include <usagi/concepts/ui/drawable.h>

template <class DrawableType>
struct Drawable
{
  using draw_type = DrawableType;
  void draw(draw_type &draw);
};

template <class DrawableType>
struct UnDrawable
{
  using draw_type = DrawableType;
  // void draw(draw_type &draw);
};

struct DrawContext
{
};

bool
DrawableStaticTest()
{
  static_assert(usagi::concepts::ui::drawable<Drawable<DrawContext>>);
  static_assert(!usagi::concepts::ui::drawable<UnDrawable<DrawContext>>);

  return true;
}

TEST(DrawableTest, StaticCase)
{
  ASSERT_TRUE(DrawableStaticTest());
}
