#include <vector>

#include <usagi/ui/surface.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext final {
  constexpr explicit DrawContext(std::vector<int> &s) : stamp{s} {}

  void tick() { stamp.emplace_back(1); }

private:
  std::vector<int> &stamp;
};

using base_view =
    usagi::ui::base_view<int, DrawContext, usagi::type::gesture_default_parameter<int>>;
using func_type = std::function<void(typename base_view::draw_context_type &, const base_view &)>;

static_assert(usagi::concepts::ui::viewable<usagi::ui::surface<base_view, func_type>>);
} // namespace
