/*#include <gtest/gtest.h>
#include <usagi/ui/surface.hpp>
#include <usagi/ui/view.hpp>

struct DrawContextable {
  using draw_type = std::function<void(int)>;
  void draw(draw_type &&f) const {
    std::forward<draw_type>(f)(0);
  }
};

class SpecificView final : public usagi::ui::base_view<float, DrawContextable> {};

TEST(SurfaceTest, FuncCase) {
  using ViewType = usagi::ui::base_view<float, DrawContextable>;
  auto s = usagi::ui::surfaced<ViewType>(
      [](ViewType::draw_context_type::draw_type &canvas, const ViewType &view) {},
      usagi::geometry::rect<float>{10.f, 10.f, 40.f, 40.f});
  auto context = DrawContextable{};
  s.draw([](){});
}
*/