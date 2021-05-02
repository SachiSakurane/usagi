#include <gtest/gtest.h>
#include <usagi/concepts/parent_view.h>

struct BaseView
{
  using value_type = float;
  using affine_type = usagi::affine<value_type>;
  decltype(auto) width() const { return value_type{}; }
  decltype(auto) height() const { return value_type{}; }
  decltype(auto) transform() const { return affine_type{}; }
};

struct ParentView 
{
  using value_type = float;
  using affine_type = usagi::affine<value_type>;
  decltype(auto) width() const { return value_type{}; }
  decltype(auto) height() const { return value_type{}; }
  decltype(auto) transform() const { return affine_type{}; }
  decltype(auto) children() const { return std::make_tuple(BaseView{}, BaseView{}); }
};

struct MissParentViewConcepts
{
  using value_type = float;
  using affine_type = usagi::affine<value_type>;
  decltype(auto) width() const { return value_type{}; }
  decltype(auto) height() const { return value_type{}; }
};

bool ParentViewStaticTest()
{
  // static_assert(usagi::concepts::view<ParentView>, "ParentView has view concept");
  // static_assert(usagi::concepts::parent_view<ParentView>, "ViewConcepts<int> hasn't view concept");
  // static_assert(!usagi::concepts::view<MissViewConcepts>, "MissViewConcepts hasn't view concept");
  return true;
}

TEST(ParentViewConceptTest, StaticTest)
{
  ASSERT_TRUE(ParentViewStaticTest());
}