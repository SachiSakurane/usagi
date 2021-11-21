#include <string>

#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_default_parameter<float>;

static_assert(
    usagi::concepts::ui::viewable<usagi::ui::view<float, DrawContext, GestureParameterType>>);

namespace view_holder_ {
  using BaseView = usagi::ui::base_view<float, DrawContext, GestureParameterType>;
  struct SpecificView : BaseView {
    constexpr SpecificView(int, std::nullptr_t) : BaseView{} {}
  };

  static_assert(usagi::concepts::ui::viewable<usagi::ui::detail::view_holder<BaseView>>);
  static_assert(usagi::concepts::ui::viewable<usagi::ui::detail::view_holder<SpecificView>>);
  static_assert([]() constexpr {
    usagi::ui::detail::view_holder<BaseView> default_construct{};
    // usagi::ui::detail::view_holder<BaseView> copy_construct{default_construct};
    // usagi::ui::detail::view_holder<BaseView> move_construct{std::move(default_construct)};

    // usagi::ui::detail::view_holder<SpecificView> specific_construct{0, nullptr};
    return true;
  }());
} // namespace view_holder_
} // namespace
