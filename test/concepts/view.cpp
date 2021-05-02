#include <gtest/gtest.h>
#include <usagi/concepts/view.h>

template <class Type>
struct View
{
  using value_type = Type;
  decltype(auto) width() const { return value_type{}; }
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

  return true;
}

TEST(ViewConceptTest, StaticTest)
{
  ASSERT_TRUE(ViweStaticTest());
}