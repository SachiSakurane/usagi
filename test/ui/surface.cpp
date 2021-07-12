#include <gtest/gtest.h>
#include <usagi/ui/surface.hpp>
#include <usagi/ui/view.hpp>

#include "../mocks/draw_context.hpp"

TEST(SurfaceTest, FuncCase) {
  using ViewType = usagi::ui::base_view<float, DrawContext>;
  auto s = usagi::ui::surfaced<ViewType>(
      [](ViewType::draw_context_type &, const ViewType &) {},
      usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f});
  auto context = DrawContext{};
  s.draw(context);
}
