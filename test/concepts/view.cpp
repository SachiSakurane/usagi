#include <gtest/gtest.h>
#include <usagi/concepts/view.h>

template <class Type>
struct ViewConcepts
{
  using value_type = Type;
  value_type width, height;
  usagi::affine<value_type> affine;
};

struct MissViewConcepts
{
  using value_type = float;
  value_type width, height;
};

bool ViweStaticTest()
{
  static_assert(usagi::concepts::view<ViewConcepts<float>>, "ViewConcepts<int> has view concept");
  static_assert(!usagi::concepts::view<ViewConcepts<int>>, "ViewConcepts<int> hasn't view concept");
  static_assert(!usagi::concepts::view<MissViewConcepts>, "MissViewConcepts hasn't view concept");

  return true;
}

TEST(ViewConceptTest, StaticTest)
{
  ASSERT_TRUE(ViweStaticTest());
}