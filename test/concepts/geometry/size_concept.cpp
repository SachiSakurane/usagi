#include <usagi/concepts/geometry/size_concept.hpp>

namespace
{
  template <class ValueType>
  struct Sized
  {
    using value_type = ValueType;
    value_type width() const;
    value_type height() const;
  };

  template <class ValueType>
  struct UnSized
  {
    using value_type = ValueType;
    value_type width() const;
    // value_type height() const;
  };

  static_assert(usagi::concepts::geometry::size_concept<Sized<int>>);
  static_assert(!usagi::concepts::geometry::size_concept<UnSized<int>>);
}
