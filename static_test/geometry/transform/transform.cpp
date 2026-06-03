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

static_assert(usagi::concepts::geometry::transform_concept<usagi::geometry::transform<float>>);

static_assert([] {
  constexpr auto t = usagi::geometry::transform<float>{};

  if (t.translation().x() != 0 || t.translation().y() != 0) {
    return false;
  }
  if (t.rotation() != 0) {
    return false;
  }
  if (t.scale().x() != 1 || t.scale().y() != 1) {
    return false;
  }
  if (t.origin().x() != 0 || t.origin().y() != 0) {
    return false;
  }
  return true;
}());

static_assert([] {
  constexpr auto t =
      usagi::geometry::transform<float>{usagi::geometry::point<float>{1.f, 2.f}, 3.f,
                                        usagi::geometry::point<float>{4.f, 5.f},
                                        usagi::geometry::point<float>{6.f, 7.f}};
  constexpr auto tuple = t();
  constexpr auto copy = t.duplicate();

  if (std::get<0>(tuple) != 1 || std::get<1>(tuple) != 2 || std::get<2>(tuple) != 3 ||
      std::get<3>(tuple) != 4 || std::get<4>(tuple) != 5 || std::get<5>(tuple) != 6 ||
      std::get<6>(tuple) != 7) {
    return false;
  }
  if (copy.translation().x() != 1 || copy.translation().y() != 2) {
    return false;
  }
  if (copy.rotation() != 3) {
    return false;
  }
  if (copy.scale().x() != 4 || copy.scale().y() != 5) {
    return false;
  }
  if (copy.origin().x() != 6 || copy.origin().y() != 7) {
    return false;
  }
  return true;
}());

static_assert([] {
  constexpr auto t =
      usagi::geometry::transform<float>{PointLike<float>{}, 3.f, PointLike<float>{},
                                        PointLike<float>{}};

  if (t.translation().x() != 1 || t.translation().y() != 2) {
    return false;
  }
  if (t.rotation() != 3) {
    return false;
  }
  if (t.scale().x() != 1 || t.scale().y() != 2) {
    return false;
  }
  if (t.origin().x() != 1 || t.origin().y() != 2) {
    return false;
  }
  return true;
}());
} // namespace
