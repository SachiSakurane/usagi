#include <gtest/gtest.h>
#include <usagi/type/mouse.hpp>
#include <usagi/ui/gesture.hpp>
#include <usagi/ui/view.hpp>

// static test
namespace {
struct a_tag {};
struct b_tag {};

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

  bool event(typename mouse_traits::on_drag_type) override {
    // 2
    stamp.emplace_back(2);
    return false;
  }

  using usagi::ui::base_view<ValueType, int, MouseParameter>::event;

private:
  std::vector<int> &stamp;
};

namespace detail {
  using target_tuple = std::tuple<void, a_tag, b_tag>;

  // is_apply_invocable
  static_assert(
      usagi::ui::detail::is_apply_invocable<std::function<void(a_tag, b_tag)>, target_tuple>(
          std::make_index_sequence<std::tuple_size_v<target_tuple>>()));

  static_assert(
      !usagi::ui::detail::is_apply_invocable<std::function<void(a_tag, a_tag)>, target_tuple>(
          std::make_index_sequence<std::tuple_size_v<target_tuple>>()));

} // namespace detail

} // namespace

TEST(GestureTest, IsApplyInvocable) {
  using target = std::tuple<void, a_tag, b_tag>;
  {
    auto l = [](a_tag, b_tag) {};
    ASSERT_TRUE((usagi::ui::detail::is_apply_invocable<decltype(l), target>(
        std::make_index_sequence<std::tuple_size_v<target>>())));
  }
  {
    auto l = [](a_tag, a_tag) {};
    ASSERT_FALSE((usagi::ui::detail::is_apply_invocable<decltype(l), target>(
        std::make_index_sequence<std::tuple_size_v<target>>())));
  }
  {
    // auto が b_tag に推論される
    auto l = [](a_tag, auto) {};
    ASSERT_TRUE((usagi::ui::detail::is_apply_invocable<decltype(l), target>(
        std::make_index_sequence<std::tuple_size_v<target>>())));
  }
}

TEST(GestureTest, PickFuncWrapper) {
  // default
  {
    auto x = usagi::ui::detail::pick_func_wrapper<std::tuple<a_tag, b_tag>>(
        // candidates
        [](a_tag, a_tag) { return false; }, [](b_tag, a_tag) { return false; },
        [](b_tag, b_tag) { return false; });
    ASSERT_TRUE(x == nullptr);
  }

  // specialized
  {
    auto x = usagi::ui::detail::pick_func_wrapper<std::tuple<bool, a_tag, b_tag>>(
        // candidates
        [](a_tag, a_tag) { return false; }, [](b_tag, a_tag) { return false; },
        [](b_tag, b_tag) { return false; }, [](a_tag, b_tag) { return true; });
    ASSERT_TRUE(x(a_tag{}, b_tag{}));
  }

  // auto
  {
    auto x = usagi::ui::detail::pick_func_wrapper<std::tuple<bool, a_tag, b_tag>>(
        // candidates
        [](a_tag, a_tag) { return false; }, [](a_tag, auto) { return true; });
    ASSERT_TRUE(x(a_tag{}, b_tag{}));
  }
}

TEST(GestureTest, PickInvocable) {
  // none
  {
    auto x = usagi::ui::detail::pick_invocable<std::tuple<a_tag, b_tag>>(
        // candidates
        std::make_tuple([](a_tag, a_tag) { return false; }, [](b_tag, a_tag) { return false; },
                        [](b_tag, b_tag) { return false; }));
    ASSERT_TRUE(x == nullptr);
  }

  // specialized
  {
    auto x = usagi::ui::detail::pick_invocable<std::tuple<bool, a_tag, b_tag>>(
        // candidates
        std::make_tuple([](a_tag, a_tag) { return false; }, [](b_tag, a_tag) { return false; },
                        [](b_tag, b_tag) { return false; }, [](a_tag, b_tag) { return true; }));
    ASSERT_TRUE(x(a_tag{}, b_tag{}));
  }

  // auto
  {
    auto x = usagi::ui::detail::pick_invocable<std::tuple<bool, a_tag, b_tag>>(
        // candidates
        std::make_tuple([](a_tag, a_tag) { return true; }, [](a_tag, auto) { return true; }));
    ASSERT_TRUE(x(a_tag{}, b_tag{}));
  }
}

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
    ASSERT_FALSE(g.on_double_click);
    ASSERT_FALSE(g.on_wheel);

    ASSERT_EQ(stamp.size(), 0);
  }
}

TEST(GestureTest, Gestures) {
  using view = SpecificView<float>;

  std::vector<int> stamp;
  view v{stamp};

  // specialized
  {
    usagi::ui::gestures<view> g{std::make_tuple([&stamp](view::mouse_traits::on_drag_type, auto &) {
      stamp.emplace_back(0);
      return false;
    })};

    ASSERT_FALSE(g.on_down_holder);
    ASSERT_TRUE(g.on_drag_holder);
    ASSERT_FALSE(g.on_up_holder);
    ASSERT_FALSE(g.on_over_holder);
    ASSERT_FALSE(g.on_out_holder);
    ASSERT_FALSE(g.on_double_click);
    ASSERT_FALSE(g.on_wheel);

    g.on_drag_holder(view::mouse_traits::on_drag_type{}, v);

    // 特殊化した関数が実行されている
    ASSERT_EQ(stamp.size(), 1);
    ASSERT_EQ(stamp[0], 0);
  }
}

TEST(GestureTest, SpecializedGestures) {
  using view = SpecificView<float>;

  std::vector<int> stamp;
  auto v = view{stamp} | usagi::ui::gestured([&stamp](view::mouse_traits::on_up_type,
                                                      auto &) { stamp.emplace_back(100); },
                                             [&stamp](view::mouse_traits::on_drag_type, auto &) {
                                               stamp.emplace_back(0);
                                               return false;
                                             });

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
