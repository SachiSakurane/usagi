#include <vector>

#include <usagi/ui/surface.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext final {
  constexpr explicit DrawContext(int &s) : stamp{s} {}

  constexpr void tick() { stamp += 42; }

private:
  int &stamp;
};

using base_view =
    usagi::ui::base_view<int, DrawContext, usagi::type::gesture_default_parameter<int>>;

struct ContextFunctor final {
  constexpr void operator()(typename base_view::draw_context_type &d, const base_view &) {
    d.tick();
  }
};

static_assert(usagi::concepts::ui::viewable<usagi::ui::surface<base_view, ContextFunctor>>);
static_assert([]() consteval {
  usagi::ui::surface<base_view, ContextFunctor> s{base_view{}, ContextFunctor{}};
  int x{0};
  DrawContext context{x};
  s.draw(context);
  return x == 42;
}());
} // namespace
