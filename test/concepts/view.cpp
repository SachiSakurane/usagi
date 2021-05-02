#include <gtest/gtest.h>
#include <usagi/concepts/view.h>

template <class Type>
struct View
{
  using value_type = Type;
  value_type width;
  value_type height;
  usagi::affine<value_type> affine;
};

struct MissViewConcepts
{
  using value_type = float;
  value_type width;
};

bool ViweStaticTest()
{
  static_assert(usagi::concepts::view<View<float>>, "ViewConcepts<float> has view concept");
  static_assert(!usagi::concepts::view<View<int>>, "ViewConcepts<int> hasn't view concept");
  static_assert(!usagi::concepts::view<MissViewConcepts>, "MissViewConcepts hasn't view concept");

  return true;
}

TEST(ViewConceptTest, StaticTest)
{
  ASSERT_TRUE(ViweStaticTest());
}