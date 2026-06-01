#include <usagi/concepts/type/gestural_parameter.hpp>
#include <usagi/geometry/point.hpp>
#include <usagi/type/gesture.hpp>

namespace {
struct UnGesturalParameter {
  using value_type = float;
  float x;
  float y;
  float d;
};

struct MismatchedPositionValueType {
  using value_type = float;
  usagi::geometry::point<int> position;
  float wheel_delta;
  bool l, r, shift, ctrl, alt;
};

static_assert(
    usagi::concepts::type::gestural_parameter<usagi::type::gesture_parameter<float>>);
static_assert(!usagi::concepts::type::gestural_parameter<UnGesturalParameter>);
static_assert(!usagi::concepts::type::gestural_parameter<MismatchedPositionValueType>);
} // namespace
