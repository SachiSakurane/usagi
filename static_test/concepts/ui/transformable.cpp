#include <usagi/concepts/ui/transformable.hpp>
#include <usagi/geometry/point/point.hpp>
#include <usagi/geometry/transform/transform.hpp>

namespace {
template <class ValueType>
struct Transformable {
  using value_type = ValueType;
  using point_type = usagi::geometry::point<value_type>;
  using transform_type = usagi::geometry::transform<value_type>;

  transform_type transform() const;
  void set_transform(transform_type);

  point_type translation() const;
  void set_translation(point_type);

  point_type scale() const;
  void set_scale(point_type);
  void set_scale(point_type, point_type);
};

template <class ValueType>
struct UnTransformable {
  using value_type = ValueType;
  using point_type = usagi::geometry::point<value_type>;
  using transform_type = usagi::geometry::transform<value_type>;

  transform_type transform() const;
  void set_transform(transform_type);

  point_type translation() const;
  void set_translation(point_type);

  point_type scale() const;
  void set_scale(point_type);
  // void set_scale(point_type, point_type);
};

static_assert(usagi::concepts::ui::transformable<Transformable<int>>);
static_assert(!usagi::concepts::ui::transformable<UnTransformable<int>>);
} // namespace
