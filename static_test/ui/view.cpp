#include <string>
#include <type_traits>

#include <usagi/concepts/ui/transformable.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/view.hpp>
#include <usagi/ui/view_interface.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_parameter<float>;

static_assert(
    usagi::concepts::ui::viewable<usagi::ui::view<float, DrawContext, GestureParameterType>>);
static_assert(usagi::concepts::ui::transformable<
              usagi::ui::view<float, DrawContext, GestureParameterType>>);
static_assert(std::is_abstract_v<usagi::ui::view_interface<float, DrawContext, GestureParameterType>>);
static_assert(!std::is_default_constructible_v<usagi::ui::view<float, DrawContext, GestureParameterType>>);

namespace view_holder_ {
  using BaseView = usagi::ui::base_view<float, DrawContext, GestureParameterType>;
  struct SpecificView : BaseView {
    constexpr SpecificView(int, std::nullptr_t) : BaseView{} {}
  };

  static_assert(usagi::concepts::ui::viewable<usagi::ui::detail::view_holder<BaseView>>);
  static_assert(usagi::concepts::ui::transformable<usagi::ui::detail::view_holder<BaseView>>);
  static_assert(usagi::concepts::ui::viewable<usagi::ui::detail::view_holder<SpecificView>>);
  static_assert(usagi::concepts::ui::transformable<
                usagi::ui::detail::view_holder<SpecificView>>);
} // namespace view_holder_
} // namespace
