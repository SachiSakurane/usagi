#include <vector>

#include <usagi/ui/surface.hpp>
#include <usagi/ui/base_view.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct DrawContext final {
  constexpr explicit DrawContext(int &s) : stamp{s} {}

  constexpr void tick() { stamp += 42; }

private:
  int &stamp;
};

using base_view = usagi::ui::base_view<int, DrawContext, usagi::type::gesture_parameter<int>>;

struct ContextFunctor final {
  constexpr void operator()(typename base_view::draw_context_type &d,
                            typename base_view::offset_type offset, const base_view &) {
    d.tick();
  }
};

struct MoveOnlyFunctor final {
  constexpr MoveOnlyFunctor() = default;
  constexpr MoveOnlyFunctor(MoveOnlyFunctor &&) = default;
  constexpr MoveOnlyFunctor &operator=(MoveOnlyFunctor &&) = default;
  MoveOnlyFunctor(const MoveOnlyFunctor &) = delete;
  MoveOnlyFunctor &operator=(const MoveOnlyFunctor &) = delete;

  constexpr void operator()(typename base_view::draw_context_type &d,
                            typename base_view::offset_type offset, const base_view &) {
    d.tick();
  }
};

static_assert(usagi::concepts::ui::viewable<usagi::ui::surface<base_view, ContextFunctor>>);
static_assert([]() consteval {
  usagi::ui::surface<base_view, ContextFunctor> s{base_view{}, ContextFunctor{}};
  int x{0};
  DrawContext context{x};
  s.draw(context, typename base_view::offset_type{});
  return x == 42;
}());
static_assert([]() consteval {
  auto s = usagi::ui::surface{base_view{}, MoveOnlyFunctor{}};
  int x{0};
  DrawContext context{x};
  s.draw(context, typename base_view::offset_type{});
  return x == 42;
}());
static_assert([]() consteval {
  auto s = base_view{} | usagi::ui::surfaced(MoveOnlyFunctor{});
  int x{0};
  DrawContext context{x};
  s.draw(context, typename base_view::offset_type{});
  return x == 42;
}());
} // namespace
