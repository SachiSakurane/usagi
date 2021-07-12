#include <vector>

#include <gtest/gtest.h>
#include <usagi/ui/surface.hpp>
#include <usagi/ui/view.hpp>

struct DrawContext final {
  explicit DrawContext(std::vector<int> &s) : stamp{s} {}

  void tick() { stamp.emplace_back(1); }

private:
  std::vector<int> &stamp;
};

template <usagi::utility::arithmetic ValueType, class DrawContextType>
struct SpecificView final : usagi::ui::base_view<ValueType, DrawContextType> {
  using value_type = ValueType;
  using draw_context_type = DrawContextType;

  explicit SpecificView(std::vector<int> &s) : stamp{s} {}

  void draw(draw_context_type &c) {
    // 2
    stamp.emplace_back(2);
    c.tick();
  }

private:
  std::vector<int> &stamp;
};

TEST(SurfaceTest, SequentialCase) {
  std::vector<int> stamp;
  auto s =
      usagi::ui::surface<SpecificView<int, DrawContext>>{[&stamp](auto &context, const auto &) {
                                                           // 0
                                                           stamp.emplace_back(0);
                                                           context.tick();
                                                         },
                                                         stamp};
  auto context = DrawContext{stamp};
  s.draw(context);

  // 0 が先に呼ばれているので surface に渡したラムダが先に到達していることがわかる
  ASSERT_EQ(stamp[0], 0);
  ASSERT_EQ(stamp[1], 1);
  ASSERT_EQ(stamp[2], 2);
  ASSERT_EQ(stamp[3], 1);
  ASSERT_EQ(stamp.size(), 4);
}

TEST(SurfaceTest, SurfacedCase) {
  std::vector<int> stamp;
  auto s = usagi::ui::surfaced<SpecificView<int, DrawContext>>(
      [&stamp](auto &context, const auto &) {
        // 0
        stamp.emplace_back(0);
        context.tick();
      },
      stamp);
  auto context = DrawContext{stamp};
  s.draw(context);

  // 0 が先に呼ばれているので surface に渡したラムダが先に到達していることがわかる
  ASSERT_EQ(stamp[0], 0);
  ASSERT_EQ(stamp[1], 1);
  ASSERT_EQ(stamp[2], 2);
  ASSERT_EQ(stamp[3], 1);
  ASSERT_EQ(stamp.size(), 4);
}
