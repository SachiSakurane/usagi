#include <gtest/gtest.h>
#include <usagi/concepts/ui/contentable.h>
#include <usagi/geometry/size/size.h>

template <class ValueType>
struct Contentable
{
  using value_type = ValueType;
  using size_type = typename usagi::size<value_type>;
  size_type bounds() const;
};

template <class ValueType>
struct UnContentable
{
  using value_type = ValueType;
  using size_type = typename usagi::size<value_type>;
  value_type bounds() const;
};

bool ContentableStaticTest()
{
  static_assert(usagi::concepts::ui::contentable<Contentable<int>>);
  static_assert(!usagi::concepts::ui::contentable<UnContentable<int>>);

  return true;
}

TEST(ContentableTest, StaticCase)
{
  ASSERT_TRUE(ContentableStaticTest());
}
