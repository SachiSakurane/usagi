#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/concepts/ui/transformable.hpp>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/base_view.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_parameter<float>;
using BaseViewType = usagi::ui::base_view<float, DrawContext, GestureParameterType>;

static_assert(usagi::concepts::ui::viewable<BaseViewType>);
static_assert(usagi::concepts::ui::transformable<BaseViewType>);
static_assert([]() consteval {
  BaseViewType default_construct, rect_construct{BaseViewType::rect_type{}};
  return true;
}());

// drawable
static_assert([]() consteval {
  BaseViewType view;
  DrawContext context;
  view.draw(context, typename BaseViewType::offset_type{});
  return true;
}());

// gestural
// static_assert([]() consteval {
//  using gesture_traits = BaseViewType::gesture_traits;
//  BaseViewType view;
//  view.event(gesture_traits::on_down_type{});
//  return true;
//}());

// viewable
static_assert([]() consteval {
  BaseViewType view{BaseViewType::rect_type{1.f, 1.f, 3.f, 3.f}};

  if (view.bounds() != BaseViewType::size_type{2.f, 2.f}) {
    return false;
  }

  if (view.frame() != BaseViewType::rect_type{1.f, 1.f, 3.f, 3.f}) {
    return false;
  }

  return true;
}());

// transformable
static_assert([]() consteval {
  BaseViewType view;

  view.set_transform(BaseViewType::transform_type{BaseViewType::point_type{9.f, 10.f}, 11.f,
                                                  BaseViewType::point_type{12.f, 13.f},
                                                  BaseViewType::point_type{14.f, 15.f}});
  if (view.transform().translation() != BaseViewType::point_type{9.f, 10.f}) {
    return false;
  }
  if (view.transform().rotation() != 11.f) {
    return false;
  }
  if (view.transform().scale() != BaseViewType::point_type{12.f, 13.f}) {
    return false;
  }
  if (view.transform().origin() != BaseViewType::point_type{14.f, 15.f}) {
    return false;
  }

  view.set_translation(BaseViewType::point_type{1.f, 2.f});
  if (view.translation() != BaseViewType::point_type{1.f, 2.f}) {
    return false;
  }
  if (view.transform().rotation() != 11.f) {
    return false;
  }

  view.set_scale(BaseViewType::point_type{3.f, 4.f});
  if (view.scale() != BaseViewType::point_type{3.f, 4.f}) {
    return false;
  }
  if (view.transform().origin() != BaseViewType::point_type{14.f, 15.f}) {
    return false;
  }

  view.set_scale(BaseViewType::point_type{5.f, 6.f}, BaseViewType::point_type{7.f, 8.f});
  const auto transform = view.transform();
  if (transform.translation() != BaseViewType::point_type{1.f, 2.f}) {
    return false;
  }
  if (transform.rotation() != 11.f) {
    return false;
  }
  if (transform.scale() != BaseViewType::point_type{5.f, 6.f}) {
    return false;
  }
  if (transform.origin() != BaseViewType::point_type{7.f, 8.f}) {
    return false;
  }

  return true;
}());

} // namespace
