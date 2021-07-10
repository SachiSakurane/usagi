#include <usagi/concepts/geometry/rect_concept.hpp>
#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/size/size.hpp>

namespace {
template <class ValueType>
struct Rected {
  using value_type = ValueType;
  value_type l() const;
  value_type t() const;
  value_type r() const;
  value_type b() const;
  usagi::geometry::size<value_type> size() const;
  usagi::geometry::point<value_type> center() const;
};

template <class ValueType>
struct UnRected {
  using value_type = ValueType;
  value_type l() const;
  value_type t() const;
  value_type r() const;
  // value_type b() const;
  usagi::geometry::size<value_type> size() const;
  usagi::geometry::point<value_type> center() const;
};

static_assert(usagi::concepts::geometry::rect_concept<Rected<int>>);
static_assert(!usagi::concepts::geometry::rect_concept<UnRected<int>>);
} // namespace
