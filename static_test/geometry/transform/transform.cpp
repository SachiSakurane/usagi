#include <tuple>

#include <usagi/concepts/geometry/transform_concept.hpp>
#include <usagi/geometry/transform/transform.hpp>

namespace {
template <class ValueType>
struct PointLike {
  using value_type = ValueType;

  constexpr ValueType x() const { return 1; }
  constexpr ValueType y() const { return 2; }
};

static_assert(usagi::concepts::geometry::transform_concept<usagi::geometry::transform<int>>);

static_assert([] {
  constexpr auto t = usagi::geometry::transform<int>{};

  if (t.translation().x() != 0 || t.translation().y() != 0) {
    return false;
  }
  if (t.rotation() != 0) {
    return false;
  }
  if (t.origin().x() != 0 || t.origin().y() != 0) {
    return false;
  }
  return true;
}());

static_assert([] {
  constexpr auto t =
      usagi::geometry::transform<int>{usagi::geometry::point<int>{1, 2}, 3,
                                      usagi::geometry::point<int>{4, 5}};
  constexpr auto tuple = t();
  constexpr auto copy = t.duplicate();

  if (std::get<0>(tuple) != 1 || std::get<1>(tuple) != 2 || std::get<2>(tuple) != 3 ||
      std::get<3>(tuple) != 4 || std::get<4>(tuple) != 5) {
    return false;
  }
  if (copy.translation().x() != 1 || copy.translation().y() != 2) {
    return false;
  }
  if (copy.rotation() != 3) {
    return false;
  }
  if (copy.origin().x() != 4 || copy.origin().y() != 5) {
    return false;
  }
  return true;
}());

static_assert([] {
  constexpr auto t = usagi::geometry::transform<int>{PointLike<int>{}, 3, PointLike<int>{}};

  if (t.translation().x() != 1 || t.translation().y() != 2) {
    return false;
  }
  if (t.rotation() != 3) {
    return false;
  }
  if (t.origin().x() != 1 || t.origin().y() != 2) {
    return false;
  }
  return true;
}());
} // namespace
