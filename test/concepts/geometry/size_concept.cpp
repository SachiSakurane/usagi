#include <gtest/gtest.h>
#include <usagi/concepts/geometry/size_concept.h>
#include <usagi/geometry/size/size.h>

template <class ValueType>
struct Sized
{
  using value_type = ValueType;
  value_type width() const;
  value_type height() const;
  std::pair<value_type, value_type> operator()() const;
};

template <class ValueType>
struct UnSized
{
  using value_type = ValueType;
  value_type width() const;
  // value_type height() const;
  std::pair<value_type, value_type> operator()() const;
};

bool SizeConceptStaticTest()
{
  static_assert(usagi::concepts::geometry::size_concept<Sized<int>>);
  static_assert(!usagi::concepts::geometry::size_concept<UnSized<int>>);
  static_assert(usagi::concepts::geometry::size_concept<usagi::size<int>>);
  static_assert(usagi::concepts::geometry::size_concept<usagi::paired_size<int>>);

  return true;
}

TEST(SizeConceptStaticTest, StaticCase)
{
  ASSERT_TRUE(SizeConceptStaticTest());
}
