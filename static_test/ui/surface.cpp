#include <vector>

#include <usagi/concepts/ui/transformable.hpp>
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

using base_view = usagi::ui::base_view<float, DrawContext, usagi::type::gesture_parameter<float>>;

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

struct MutableViewFunctor final {
  constexpr void operator()(typename base_view::draw_context_type &d,
                            typename base_view::offset_type offset, base_view &) {
    d.tick();
  }
};

template <class HandlerType>
concept surfaceable = requires {
  typename usagi::ui::surface<base_view, HandlerType>;
};

static_assert(usagi::concepts::ui::viewable<
              usagi::ui::surface<base_view, decltype(usagi::ui::on_draw(ContextFunctor{}))>>);
static_assert(usagi::concepts::ui::transformable<
              usagi::ui::surface<base_view, decltype(usagi::ui::on_draw(ContextFunctor{}))>>);
static_assert(!surfaceable<decltype(usagi::ui::on_draw(MutableViewFunctor{}))>);
static_assert([]() consteval {
  usagi::ui::surface s{base_view{}, usagi::ui::on_draw(ContextFunctor{})};
  int x{0};
  DrawContext context{x};
  s.draw(context, typename base_view::offset_type{});
  return x == 42;
}());
static_assert([]() consteval {
  auto s = usagi::ui::surface{base_view{}, usagi::ui::on_draw(MoveOnlyFunctor{})};
  int x{0};
  DrawContext context{x};
  s.draw(context, typename base_view::offset_type{});
  return x == 42;
}());
static_assert([]() consteval {
  auto s = base_view{} | usagi::ui::surfaced(usagi::ui::on_draw(MoveOnlyFunctor{}));
  int x{0};
  DrawContext context{x};
  s.draw(context, typename base_view::offset_type{});
  return x == 42;
}());
static_assert([]() consteval {
  auto s = usagi::ui::surface{base_view{}, usagi::ui::on_draw(ContextFunctor{})};

  s.set_transform(decltype(s)::transform_type{decltype(s)::point_type{1, 2}, 3,
                                              decltype(s)::point_type{4, 5},
                                              decltype(s)::point_type{6, 7}});
  if (s.transform().translation() != decltype(s)::point_type{1, 2}) {
    return false;
  }

  s.set_translation(decltype(s)::point_type{8, 9});
  s.set_rotation(14, decltype(s)::point_type{15, 16});
  s.set_scale(decltype(s)::point_type{10, 11}, decltype(s)::point_type{12, 13});

  return s.translation() == decltype(s)::point_type{8, 9} &&
      s.rotation() == 14 &&
      s.scale() == decltype(s)::point_type{10, 11} &&
      s.transform().origin() == decltype(s)::point_type{12, 13};
}());
} // namespace
