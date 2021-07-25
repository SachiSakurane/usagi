#include <gtest/gtest.h>
#include <usagi/ui/gesture.hpp>
#include <usagi/ui/view.hpp>

// static test
namespace {
struct a_tag {};
struct b_tag {};

template <usagi::utility::arithmetic ValueType>
struct SpecificView final : usagi::ui::base_view<ValueType, int> {
  using value_type = ValueType;
  using draw_context_type = int;
  using mouse_traits = typename usagi::ui::base_view<ValueType, int>::mouse_traits;

  explicit SpecificView(std::vector<int> &s) : stamp{s} {}

  void event(typename mouse_traits::on_down_type) override {
    // 1
    stamp.emplace_back(1);
  }

  void event(typename mouse_traits::on_drag_type) override {
    // 2
    stamp.emplace_back(2);
  }

  using usagi::ui::base_view<ValueType, int>::event;

private:
  std::vector<int> &stamp;
};

namespace detail {
  using target_tuple = std::tuple<a_tag, b_tag>;

  // is_apply_invocable
  static_assert(
      !usagi::ui::detail::is_apply_invocable<std::function<void(a_tag, a_tag)>, target_tuple>(
          std::make_index_sequence<std::tuple_size_v<target_tuple>>()));
  static_assert(
      usagi::ui::detail::is_apply_invocable<std::function<void(a_tag, b_tag)>, target_tuple>(
          std::make_index_sequence<std::tuple_size_v<target_tuple>>()));
} // namespace detail

} // namespace

TEST(GestureTest, IsApplyInvocable) {
  using target = std::tuple<a_tag, b_tag>;
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
    auto l = [](a_tag, auto) {};
    ASSERT_TRUE((usagi::ui::detail::is_apply_invocable<decltype(l), target>(
        std::make_index_sequence<std::tuple_size_v<target>>())));
  }
}

TEST(GestureTest, PickFuncWrapper) {
  // default
  {
    auto x = usagi::ui::detail::pick_func_wrapper<std::tuple<a_tag, b_tag>>(
        // default
        [](auto, auto) { return true; },
        // candidates
        [](a_tag, a_tag) { return false; }, [](b_tag, a_tag) { return false; },
        [](b_tag, b_tag) { return false; })(a_tag{}, b_tag{});
    ASSERT_TRUE(x);
  }

  // specialized
  {
    auto x = usagi::ui::detail::pick_func_wrapper<std::tuple<a_tag, b_tag>>(
        // default
        [](auto, auto) { return false; },
        // candidates
        [](a_tag, a_tag) { return false; }, [](b_tag, a_tag) { return false; },
        [](b_tag, b_tag) { return false; }, [](a_tag, b_tag) { return true; })(a_tag{}, b_tag{});
    ASSERT_TRUE(x);
  }

  // auto
  {
    auto x = usagi::ui::detail::pick_func_wrapper<std::tuple<a_tag, b_tag>>(
        // default
        [](auto, auto) { return false; },
        // candidates
        [](a_tag, a_tag) { return false; }, [](a_tag, auto) { return true; })(a_tag{}, b_tag{});
    ASSERT_TRUE(x);
  }
}

TEST(GestureTest, PickInvocable) {
  // default
  {
    auto x = usagi::ui::detail::pick_invocable<std::tuple<a_tag, b_tag>>(
        // candidates
        std::make_tuple([](a_tag, a_tag) { return false; }, [](b_tag, a_tag) { return false; },
                        [](b_tag, b_tag) { return false; }),
        // default
        [](auto, auto) { return true; })(a_tag{}, b_tag{});
    ASSERT_TRUE(x);
  }

  // specialized
  {
    auto x = usagi::ui::detail::pick_invocable<std::tuple<a_tag, b_tag>>(
        // candidates
        std::make_tuple([](a_tag, a_tag) { return false; }, [](b_tag, a_tag) { return false; },
                        [](b_tag, b_tag) { return false; }, [](a_tag, b_tag) { return true; }),
        // default
        [](auto, auto) { return false; })(a_tag{}, b_tag{});
    ASSERT_TRUE(x);
  }

  // auto
  {
    auto x = usagi::ui::detail::pick_invocable<std::tuple<a_tag, b_tag>>(
        // candidates
        std::make_tuple([](a_tag, a_tag) { return true; }, [](a_tag, auto) { return true; }),
        // default
        [](auto, auto) { return true; })(a_tag{}, b_tag{});
    ASSERT_TRUE(x);
  }
}

TEST(GestureTest, Gestures) {
  using view = SpecificView<float>;

  std::vector<int> stamp;
  view v{stamp};

  // default
  {
    usagi::ui::gestures<view> g{std::make_tuple()};
    g.on_down_holder(view::mouse_traits::on_down_type{}, v);
    g.on_drag_holder(view::mouse_traits::on_drag_type{}, v);
    g.on_up_holder(view::mouse_traits::on_up_type{}, v);

    ASSERT_EQ(stamp.size(), 0);
  }
  stamp.clear();

  // specialized
  {
    usagi::ui::gestures<view> g{std::make_tuple(
        [&stamp](view::mouse_traits::on_drag_type, auto &) { stamp.emplace_back(0); })};

    g.on_down_holder(view::mouse_traits::on_down_type{}, v);

    ASSERT_EQ(stamp.size(), 0);

    stamp.clear();

    g.on_drag_holder(view::mouse_traits::on_drag_type{}, v);

    // 特殊化した関数が実行されている
    ASSERT_EQ(stamp.size(), 1);
    ASSERT_EQ(stamp[0], 0);
  }
}

TEST(GestureTest, Gesture) {
  using view = SpecificView<float>;

  std::vector<int> stamp;
  auto v = view{stamp} | usagi::ui::gestured([&stamp](view::mouse_traits::on_drag_type, auto &) {
             stamp.emplace_back(0);
           });

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
