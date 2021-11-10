#include <gtest/gtest.h>
#include <usagi/type/mouse.hpp>
#include <usagi/ui/gesture.hpp>
#include <usagi/ui/view.hpp>

namespace {
struct a_tag {};
struct b_tag {};
} // namespace

TEST(GestureTest, AutoDeductionTest) {
  using target = std::tuple<void, a_tag, b_tag>;

  // auto が b_tag に推論される
  auto l = [](a_tag, auto) {};
  ASSERT_TRUE((usagi::ui::detail::is_apply_invocable<decltype(l), target>(
      std::make_index_sequence<std::tuple_size_v<target>>())));

  // auto が b_tag に推論される
  auto x = usagi::ui::detail::pick_func_wrapper<std::tuple<bool, a_tag, b_tag>>(
      // candidates
      [](a_tag, a_tag) { return false; }, [](a_tag, auto) { return true; });
  ASSERT_TRUE(x(a_tag{}, b_tag{}));
}

namespace {
using MouseParameter = usagi::type::mouse::default_parameter<float>;

template <usagi::utility::arithmetic ValueType>
struct SpecificView final : usagi::ui::base_view<ValueType, int, MouseParameter> {
  using value_type = ValueType;
  using draw_context_type = int;
  using mouse_traits = typename usagi::ui::base_view<ValueType, int, MouseParameter>::mouse_traits;

  explicit SpecificView(std::vector<int> &s) : stamp{s} {}

  bool event(typename mouse_traits::on_down_type) override {
    // 1
    stamp.emplace_back(1);
    return false;
  }

  void event(typename mouse_traits::on_drag_type) override {
    // 2
    stamp.emplace_back(2);
  }

  using usagi::ui::base_view<ValueType, int, MouseParameter>::event;

private:
  std::vector<int> &stamp;
};
} // namespace

TEST(GestureTest, NullGestures) {
  using view = SpecificView<float>;

  std::vector<int> stamp;
  view v{stamp};

  // default
  {
    usagi::ui::gestures<view> g{std::make_tuple()};

    ASSERT_FALSE(g.on_down_holder);
    ASSERT_FALSE(g.on_drag_holder);
    ASSERT_FALSE(g.on_up_holder);
    ASSERT_FALSE(g.on_over_holder);
    ASSERT_FALSE(g.on_out_holder);
    ASSERT_FALSE(g.on_double_holder);
    ASSERT_FALSE(g.on_wheel_holder);

    ASSERT_EQ(stamp.size(), 0);
  }
}

TEST(GestureTest, Gestures) {
  using view = SpecificView<float>;

  std::vector<int> stamp;
  view v{stamp};

  // specialized
  {
    usagi::ui::gestures<view> g{std::make_tuple(
        [&stamp](view::mouse_traits::on_drag_type, auto &) { stamp.emplace_back(0); })};

    ASSERT_FALSE(g.on_down_holder);
    ASSERT_TRUE(g.on_drag_holder);
    ASSERT_FALSE(g.on_up_holder);
    ASSERT_FALSE(g.on_over_holder);
    ASSERT_FALSE(g.on_out_holder);
    ASSERT_FALSE(g.on_double_holder);
    ASSERT_FALSE(g.on_wheel_holder);

    g.on_drag_holder(view::mouse_traits::on_drag_type{}, v);

    // 特殊化した関数が実行されている
    ASSERT_EQ(stamp.size(), 1);
    ASSERT_EQ(stamp[0], 0);
  }
}

TEST(GestureTest, NullGestured) {
  using view = usagi::ui::base_view<float, int, MouseParameter>;
  auto v = view{} | usagi::ui::gestured();

  {
    v.event(view::mouse_traits::on_down_type{});
    v.event(view::mouse_traits::on_drag_type{});
    v.event(view::mouse_traits::on_up_type{});
    v.event(view::mouse_traits::on_over_type{});
    v.event(view::mouse_traits::on_out_type{});
    v.event(view::mouse_traits::on_double_type{});
    v.event(view::mouse_traits::on_wheel_type{});
  }
}

TEST(GestureTest, Gestured) {
  using view = usagi::ui::base_view<float, int, MouseParameter>;
  std::vector<int> stamp;
  auto v =
      view{} | usagi::ui::gestured(
                   [&stamp](view::mouse_traits::on_down_type, auto &) {
                     stamp.emplace_back(0);
                     return true;
                   },
                   [&stamp](view::mouse_traits::on_drag_type, auto &) { stamp.emplace_back(1); },
                   [&stamp](view::mouse_traits::on_up_type, auto &) { stamp.emplace_back(2); },
                   [&stamp](view::mouse_traits::on_over_type, auto &) {
                     stamp.emplace_back(3);
                     return true;
                   },
                   [&stamp](view::mouse_traits::on_out_type, auto &) { stamp.emplace_back(4); },
                   [&stamp](view::mouse_traits::on_double_type, auto &) {
                     stamp.emplace_back(5);
                     return true;
                   },
                   [&stamp](view::mouse_traits::on_wheel_type, auto &) {
                     stamp.emplace_back(6);
                     return true;
                   });

  {
    v.event(view::mouse_traits::on_down_type{});
    v.event(view::mouse_traits::on_drag_type{});
    v.event(view::mouse_traits::on_up_type{});
    v.event(view::mouse_traits::on_over_type{});
    v.event(view::mouse_traits::on_out_type{});
    v.event(view::mouse_traits::on_double_type{});
    v.event(view::mouse_traits::on_wheel_type{});

    ASSERT_EQ(stamp.size(), 7);

    const auto pred = std::vector{{0, 1, 2, 3, 4, 5, 6}};
    ASSERT_TRUE(stamp == pred);
  }
}

TEST(GestureTest, SpecializedGestured) {
  using view = SpecificView<float>;

  std::vector<int> stamp;
  auto v = view{stamp} |
           usagi::ui::gestured(
               [&stamp](view::mouse_traits::on_up_type, auto &) { stamp.emplace_back(100); },
               [&stamp](view::mouse_traits::on_drag_type, auto &) { stamp.emplace_back(0); });

  {
    v.event(view::mouse_traits::on_up_type{});

    // gesturedのon_up_typeだけ実行されている
    ASSERT_EQ(stamp.size(), 1);
    ASSERT_EQ(stamp[0], 100);
  }

  stamp.clear();

  {
    v.event(view::mouse_traits::on_down_type{});

    // SpecificView<float>の中身だけ実行されている
    ASSERT_EQ(stamp.size(), 1);
    ASSERT_EQ(stamp[0], 1);
  }

  stamp.clear();

  {
    v.event(view::mouse_traits::on_drag_type{});

    // 特殊化した関数が先に実行されている
    ASSERT_EQ(stamp.size(), 2);
    ASSERT_EQ(stamp[0], 0);
    ASSERT_EQ(stamp[1], 2);
  }
}
