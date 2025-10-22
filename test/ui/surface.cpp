#include <vector>

#include <gtest/gtest.h>
#include <usagi/ui/surface.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext final {
  explicit DrawContext(std::vector<int> &s) : stamp{s} {}

  void tick() { stamp.emplace_back(1); }

private:
  std::vector<int> &stamp;
};

template <usagi::concepts::arithmetic ValueType, class DrawContextType>
struct SpecificView final
    : usagi::ui::base_view<ValueType, DrawContextType, usagi::type::gesture_parameter<ValueType>> {
  using value_type = ValueType;
  using draw_context_type = DrawContextType;
  using offset_type = typename usagi::geometry::geometry_traits<value_type>::point_type;

  explicit SpecificView(std::vector<int> &s) : stamp{s} {}

  void draw(draw_context_type &c, offset_type offset) override {
    // 2
    stamp.emplace_back(2);
    c.tick();
  }

private:
  std::vector<int> &stamp;
};

using local_view_type = SpecificView<int, DrawContext>;
} // namespace

TEST(SurfaceTest, SequentialCase) {
  std::vector<int> stamp;
  auto s = usagi::ui::surface{local_view_type{stamp},
                              [&stamp](auto &context, auto offset, const auto &) {
                                // 0
                                stamp.emplace_back(0);
                                context.tick();
                              }};
  auto context = DrawContext{stamp};
  s.draw(context, typename local_view_type::offset_type{});

  // 0 が先に呼ばれているので surface に渡したラムダが先に到達していることがわかる
  ASSERT_EQ(stamp.size(), 4);
  ASSERT_EQ(stamp[0], 0);
  ASSERT_EQ(stamp[1], 1);
  ASSERT_EQ(stamp[2], 2);
  ASSERT_EQ(stamp[3], 1);
}

TEST(SurfaceTest, SurfacedCase) {
  std::vector<int> stamp;
  auto s = local_view_type{stamp} |
           usagi::ui::surfaced([&stamp](auto &context, auto offset, const auto &) {
             // 0
             stamp.emplace_back(0);
             context.tick();
           });
  auto context = DrawContext{stamp};
  s.draw(context, typename local_view_type::offset_type{});

  // 0 が先に呼ばれているので surface に渡したラムダが先に到達していることがわかる
  ASSERT_EQ(stamp.size(), 4);
  ASSERT_EQ(stamp[0], 0);
  ASSERT_EQ(stamp[1], 1);
  ASSERT_EQ(stamp[2], 2);
  ASSERT_EQ(stamp[3], 1);
}
