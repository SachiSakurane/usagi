#include <gtest/gtest.h>
#include <usagi/concepts/view.h>

template <class Type>
struct View
{
  using value_type = Type;
  using affine_type = usagi::affine<value_type>;
  decltype(auto) width() const { return value_type{}; }
  decltype(auto) height() const { return value_type{}; }
  decltype(auto) transform() const { return affine_type{}; }
};

struct MissViewConcepts
{
  using value_type = float;
  using affine_type = usagi::affine<value_type>;
  decltype(auto) width() const { return value_type{}; }
  decltype(auto) height() const { return value_type{}; }
};

bool ViweStaticTest()
{
  static_assert(usagi::concepts::view<View<float>>, "ViewConcepts<float> has view concept");
  static_assert(!usagi::concepts::view<View<int>>, "ViewConcepts<int> hasn't view concept");
  // static_assert(!usagi::concepts::view<MissViewConcepts>, "MissViewConcepts hasn't view concept");
  return true;
}

TEST(ViewConceptTest, StaticTest)
{
  ASSERT_TRUE(ViweStaticTest());
}