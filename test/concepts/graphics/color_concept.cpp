#include <gtest/gtest.h>
#include <usagi/concepts/graphics/color_concept.h>

template <class ValueType>
struct Colored
{
  using value_type = ValueType;
  value_type r() const;
  value_type g() const;
  value_type b() const;
  value_type a() const;
};

template <class ValueType>
struct UnColored
{
  using value_type = ValueType;
  value_type r() const;
  value_type g() const;
  // value_type b() const;
  value_type a() const;
};

bool ColorConceptStaticTest()
{
  static_assert(usagi::concepts::graphics::color_concept<Colored<int>>);
  static_assert(!usagi::concepts::graphics::color_concept<UnColored<int>>);

  return true;
}

TEST(ColorConceptTest, StaticCase)
{
  ASSERT_TRUE(ColorConceptStaticTest());
}
