#include <vector>

#include <usagi/ui/surface.hpp>
#include <usagi/ui/view.hpp>

// static test
namespace {
struct DrawContext final {
  explicit DrawContext(std::vector<int> &s) : stamp{s} {}

  void tick() { stamp.emplace_back(1); }

private:
  std::vector<int> &stamp;
};

template <usagi::utility::arithmetic ValueType, class DrawContextType>
struct SpecificView final : usagi::ui::base_view<ValueType, DrawContextType,
                                                 usagi::type::mouse::default_parameter<ValueType>> {
  using value_type = ValueType;
  using draw_context_type = DrawContextType;

  explicit SpecificView(std::vector<int> &s) : stamp{s} {}

  void draw(draw_context_type &c) override {
    // 2
    stamp.emplace_back(2);
    c.tick();
  }

private:
  std::vector<int> &stamp;
};

using local_view_type = SpecificView<int, DrawContext>;
static_assert(
    usagi::concepts::ui::viewable<usagi::ui::surface<
        local_view_type, std::function<void(typename local_view_type::draw_context_type &,
                                            const local_view_type &)>>>,
    "usagi::ui::surface<local_view_type, std::function<void(typename "
    "local_view_type::draw_context_type &, const local_view_type &)>> has viewable concept");
} // namespace
