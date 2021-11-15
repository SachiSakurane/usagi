#include <gtest/gtest.h>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/rect/operator.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext {};
using GestureParameterType = usagi::type::gesture_default_parameter<float>;
class SpecificView final : public usagi::ui::base_view<float, DrawContext, GestureParameterType> {};
} // namespace

TEST(ViewHierarchyTest, SubViewCase) {
  auto v = usagi::ui::view{SpecificView{}};

  ASSERT_FALSE(v.remove_sub_view(0));

  {
    decltype(auto) sub = v.add_sub_view(SpecificView{});
    ASSERT_TRUE(static_cast<bool>(sub.second));
    decltype(auto) get_sub = v.get_sub_view(sub.first);
    ASSERT_EQ(&sub.second, &get_sub);
    ASSERT_TRUE(v.remove_sub_view(sub.first));
  }
  ASSERT_EQ(v.sub_view_size(), 0);

  decltype(auto) sub1 = v.add_sub_view(usagi::ui::base_view<float, DrawContext, GestureParameterType>{});
  ASSERT_EQ(v.sub_view_size(), 1);

  decltype(auto) sub2 = v.add_sub_view(usagi::ui::base_view<float, DrawContext, GestureParameterType>{});
  ASSERT_EQ(v.sub_view_size(), 2);

  ASSERT_TRUE(v.remove_sub_view(sub1.first));
  ASSERT_EQ(v.sub_view_size(), 1);

  ASSERT_TRUE(v.remove_sub_view(sub2.first));
  ASSERT_EQ(v.sub_view_size(), 0);

  ASSERT_FALSE(v.remove_sub_view(0));
}