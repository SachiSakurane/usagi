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

  value_type rotation() const;
  void set_rotation(value_type);
  void set_rotation(value_type, point_type);

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

  value_type rotation() const;
  void set_rotation(value_type);
  void set_rotation(value_type, point_type);

  point_type scale() const;
  void set_scale(point_type);
  // void set_scale(point_type, point_type);
};

template <class ValueType>
struct UnRotatable {
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
struct UnRotationOrigin {
  using value_type = ValueType;
  using point_type = usagi::geometry::point<value_type>;
  using transform_type = usagi::geometry::transform<value_type>;

  transform_type transform() const;
  void set_transform(transform_type);

  point_type translation() const;
  void set_translation(point_type);

  value_type rotation() const;
  void set_rotation(value_type);

  point_type scale() const;
  void set_scale(point_type);
  void set_scale(point_type, point_type);
};

struct NonFloatingTransformable {
  using value_type = int;
  using point_type = usagi::geometry::point<float>;
  using transform_type = usagi::geometry::transform<float>;

  transform_type transform() const;
  void set_transform(transform_type);

  point_type translation() const;
  void set_translation(point_type);

  value_type rotation() const;
  void set_rotation(value_type);
  void set_rotation(value_type, point_type);

  point_type scale() const;
  void set_scale(point_type);
  void set_scale(point_type, point_type);
};

static_assert(usagi::concepts::ui::transformable<Transformable<float>>);
static_assert(!usagi::concepts::ui::transformable<NonFloatingTransformable>);
static_assert(!usagi::concepts::ui::transformable<UnTransformable<float>>);
static_assert(!usagi::concepts::ui::transformable<UnRotatable<float>>);
static_assert(!usagi::concepts::ui::transformable<UnRotationOrigin<float>>);
} // namespace
