#include <gtest/gtest.h>
#include <usagi/concepts/geometry/point_concept.h>

template <class ValueType>
struct Pointed
{
  using value_type = ValueType;
  value_type x() const;
  value_type y() const;
};

template <class ValueType>
struct UnPointed
{
  using value_type = ValueType;
  // value_type x() const;
  value_type y() const;
};

bool PointConceptStaticTest()
{
  static_assert(usagi::concepts::geometry::point_concept<Pointed<int>>);
  static_assert(!usagi::concepts::geometry::point_concept<UnPointed<int>>);

  return true;
}

TEST(PointConceptTest, StaticCase)
{
  ASSERT_TRUE(PointConceptStaticTest());
}
