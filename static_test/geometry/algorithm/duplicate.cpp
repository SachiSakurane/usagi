#include <usagi/geometry/algorithm/duplicate.hpp>
#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/rect/rect.hpp>
#include <usagi/geometry/size/size.hpp>

namespace {
static_assert([]() constexpr {
  constexpr usagi::geometry::point<float> p{2.f, 4.f};
  constexpr auto duplicated = usagi::geometry::duplicate(p);
  return duplicated.x() == 2.f && duplicated.y() == 4.f;
}());

static_assert([]() constexpr {
  constexpr usagi::geometry::size<float> s{42.f, 24.f};
  constexpr auto duplicated = usagi::geometry::duplicate(s);
  return duplicated.width() == 42.f && duplicated.height() == 24.f;
}());

static_assert([]() constexpr {
  constexpr usagi::geometry::rect<float> r{2.f, 4.f, 42.f, 24.f};
  constexpr auto duplicated = usagi::geometry::duplicate(r);
  return duplicated.l() == 2.f && duplicated.t() == 4.f && duplicated.r() == 42.f &&
      duplicated.b() == 24.f;
}());
} // namespace
