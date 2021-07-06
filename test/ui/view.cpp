#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/ui/view.hpp>

struct DrawContextable
{
  using draw_type = std::function<void()>;
  void draw(draw_type &&d) const
  {
    std::forward<draw_type>(d)();
  }
};

class SpecialView final : public usagi::ui::base_view<float, DrawContextable>
{
};

// static test
namespace
{
  static_assert(usagi::concepts::ui::viewable<usagi::ui::view<float, DrawContextable>>, "usagi::ui::view<float, DrawContextable> has viewable concept");
  static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{SpecialView{}})>, "view is constructable from SpecialView");
  static_assert(usagi::concepts::ui::viewable<decltype(usagi::ui::view{(SpecialView{})})>, "view is constructable from SpecialView");
}

TEST(ViewTest, PredicationCase)
{
  {
    auto v = usagi::ui::view<float, DrawContextable>{};
    ASSERT_FALSE(static_cast<bool>(v));
  }
  {
    auto v = usagi::ui::view{SpecialView{}};
    ASSERT_TRUE(static_cast<bool>(v));
  }
}

TEST(ViewTest, DrawCase)
{
  auto v = usagi::ui::view{SpecialView{}};
  auto context = DrawContextable {};
  v.draw(context);
}

TEST(ViewTest, SubViewCase)
{
  auto v = usagi::ui::view{SpecialView{}};
  auto& sub = v.add_sub_view(usagi::ui::base_view<float, DrawContextable>{});
  ASSERT_TRUE(static_cast<bool>(sub));
}
