#include <usagi/concepts/geometry/transform_concept.hpp>
#include <usagi/geometry/point/point.hpp>

namespace {
template <class ValueType>
struct Transformed {
  using value_type = ValueType;
  using point_type = usagi::geometry::point<value_type>;

  point_type translation() const;
  value_type rotation() const;
  point_type scale() const;
  point_type origin() const;
};

template <class ValueType>
struct UnTransformed {
  using value_type = ValueType;
  using point_type = usagi::geometry::point<value_type>;

  point_type translation() const;
  value_type rotation() const;
  point_type scale() const;
  // point_type origin() const;
};

static_assert(usagi::concepts::geometry::transform_concept<Transformed<int>>);
static_assert(!usagi::concepts::geometry::transform_concept<UnTransformed<int>>);
} // namespace
