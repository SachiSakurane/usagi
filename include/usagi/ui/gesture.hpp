#pragma once

#include <tuple>
#include <utility>

#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/utility/invocable.hpp>

namespace usagi::ui {
namespace detail {
  template <class Func, class ArgsTuple, std::size_t... Sequence>
  inline constexpr bool is_apply_invocable(std::index_sequence<Sequence...>) {
    return std::is_invocable_v<Func, std::tuple_element_t<Sequence, ArgsTuple>...>;
  }

  template <class Func, class SearchArgsTuple>
  concept apply_invocable = is_apply_invocable<Func, SearchArgsTuple>(
      std::make_index_sequence<std::tuple_size_v<SearchArgsTuple>>());

  template <class SearchArgsTuple, apply_invocable<SearchArgsTuple> Default, class... Args>
  struct pick_func;

  // iterate
  template <class SearchArgsTuple, apply_invocable<SearchArgsTuple> Default, class Front,
            class... Args>
  struct pick_func<SearchArgsTuple, Default, Front, Args...>
      : pick_func<SearchArgsTuple, Default, Args...> {
    pick_func<SearchArgsTuple, Default, Front, Args...>(Default &&d, Front &&, Args &&...args)
        : pick_func<SearchArgsTuple, Default, Args...>{std::forward<Default>(d),
                                                       std::forward<Args>(args)...} {}
  };

  // found apply_invocable
  template <class SearchArgsTuple, apply_invocable<SearchArgsTuple> Default,
            apply_invocable<SearchArgsTuple> Front, class... Args>
  struct pick_func<SearchArgsTuple, Default, Front, Args...> {
    pick_func<SearchArgsTuple, Default, Front, Args...>(Default &&, Front &&f, Args &&...)
        : elem{std::forward<Front>(f)} {}
    Front elem;
  };

  // no result(return default)
  template <class SearchArgsTuple, apply_invocable<SearchArgsTuple> Default>
  struct pick_func<SearchArgsTuple, Default> {
    explicit pick_func<SearchArgsTuple, Default>(Default &&d) : elem{std::forward<Default>(d)} {}
    Default elem;
  };

  template <class SearchArgsTuple, class... Args>
  inline constexpr decltype(auto) pick_func_wrapper(Args &&...args) {
    return pick_func<SearchArgsTuple, Args...>{std::forward<Args>(args)...}.elem;
  }

  template <class SearchArgsTuple, class Tuple, std::size_t... Sequence>
  inline constexpr decltype(auto) pick_invocable_impl(Tuple &&t, std::index_sequence<Sequence...>) {
    return pick_func_wrapper<SearchArgsTuple>(
        std::forward<std::tuple_element_t<Sequence, Tuple>>(std::get<Sequence>(t))...);
  }

  template <class SearchArgsTuple, class CandidatesTuple, class DefaultFunc>
  inline constexpr decltype(auto) pick_invocable(CandidatesTuple t, DefaultFunc &&default_func) {
    return pick_invocable_impl<SearchArgsTuple>(
        std::tuple_cat(std::forward_as_tuple(default_func), std::forward<CandidatesTuple>(t)),
        std::make_index_sequence<1 + std::tuple_size_v<CandidatesTuple>>());
  }
} // namespace detail

template <class TupleType>
struct gesture_holder {
  TupleType elem;
};

template <class TupleType>
gesture_holder(TupleType &&) -> gesture_holder<TupleType>;

template <usagi::concepts::ui::viewable ViewType>
struct gestures {
  using value_type = typename ViewType::value_type;
  using mouse_traits = typename usagi::type::mouse_traits<typename ViewType::mouse_parameter_type>;

  template <class TupleType>
  explicit gestures(TupleType t)
      : on_down_holder{usagi::ui::detail::pick_invocable<
            std::tuple<typename mouse_traits::on_down_type, ViewType &>>(t, [](auto, auto &) {})},
        on_drag_holder{usagi::ui::detail::pick_invocable<
            std::tuple<typename mouse_traits::on_drag_type, ViewType &>>(t, [](auto, auto &) {})},
        on_up_holder{usagi::ui::detail::pick_invocable<
            std::tuple<typename mouse_traits::on_up_type, ViewType &>>(t, [](auto, auto &) {})},
        on_over_holder{usagi::ui::detail::pick_invocable<
            std::tuple<typename mouse_traits::on_over_type, ViewType &>>(t, [](auto, auto &) {})},
        on_out_holder{usagi::ui::detail::pick_invocable<
            std::tuple<typename mouse_traits::on_out_type, ViewType &>>(t, [](auto, auto &) {})},
        on_double_click_type{usagi::ui::detail::pick_invocable<
            std::tuple<typename mouse_traits::on_double_click_type, ViewType &>>(
            t, [](auto, auto &) {})} {}

  std::function<void(typename mouse_traits::on_down_type, ViewType &)> on_down_holder;
  std::function<void(typename mouse_traits::on_drag_type, ViewType &)> on_drag_holder;
  std::function<void(typename mouse_traits::on_up_type, ViewType &)> on_up_holder;
  std::function<void(typename mouse_traits::on_over_type, ViewType &)> on_over_holder;
  std::function<void(typename mouse_traits::on_out_type, ViewType &)> on_out_holder;
  std::function<void(typename mouse_traits::on_double_click_type, ViewType &)> on_double_click_type;
};

template <usagi::concepts::ui::viewable ViewType>
struct gesture {
  using value_type = typename ViewType::value_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = typename ViewType::draw_context_type;
  using mouse_parameter_type = typename ViewType::mouse_parameter_type;
  using mouse_traits = typename usagi::type::mouse_traits<mouse_parameter_type>;
  using view_type = typename ViewType::view_type;

  using children_type = typename ViewType::children_type;
  using children_key_type = typename ViewType::children_key_type;
  using children_mapped_type = typename ViewType::children_mapped_type;
  using children_value_type = typename ViewType::children_value_type;

  template <class TupleType>
  gesture(ViewType &&v, TupleType &&t) : holder{std::move(v)}, g{std::forward<TupleType>(t)} {}

  void draw(draw_context_type &context) { holder.draw(context); }

  size_type bounds() const { return holder.bounds(); }
  rect_type frame() const { return holder.frame(); }

  void event(typename mouse_traits::on_down_type mouse) {
    g.on_down_holder(mouse, holder);
    holder.event(mouse);
  }

  void event(typename mouse_traits::on_drag_type mouse) {
    g.on_drag_holder(mouse, holder);
    holder.event(mouse);
  }

  void event(typename mouse_traits::on_up_type mouse) {
    g.on_up_holder(mouse, holder);
    holder.event(mouse);
  }

  void event(typename mouse_traits::on_over_type mouse) {
    g.on_over_holder(mouse, holder);
    holder.event(mouse);
  }

  void event(typename mouse_traits::on_out_type mouse) {
    g.on_out_holder(mouse, holder);
    holder.event(mouse);
  }

  void event(typename mouse_traits::on_double_click_type mouse) {
    g.on_double_click_type(mouse, holder);
    holder.event(mouse);
  }

  void set_mouse_down(bool flag) { holder.set_mouse_down(flag); }
  void set_mouse_over(bool flag) { holder.set_mouse_over(flag); }
  [[nodiscard]] bool is_mouse_downed() const { return holder.is_mouse_downed(); }
  [[nodiscard]] bool is_mouse_overed() const { return holder.is_mouse_overed(); }

  children_value_type &add_sub_view(children_mapped_type &&sub_view) {
    return holder.add_sub_view(std::forward<children_mapped_type>(sub_view));
  }

  children_mapped_type &get_sub_view(children_key_type index) { return holder.get_sub_view(index); }

  bool remove_sub_view(children_key_type index) { return holder.remove_sub_view(index); }

  [[nodiscard]] size_t sub_view_size() const { return holder.sub_view_size(); }

  void set_enabled(bool flag) { holder.set_enabled(flag); }
  [[nodiscard]] bool is_enabled() const { return holder.is_enabled(); }

private:
  ViewType holder;
  gestures<ViewType> g;
};

template <usagi::concepts::ui::viewable ViewType, class TupleType>
inline constexpr decltype(auto) operator|(ViewType &&v, gesture_holder<TupleType> &&wrapped) {
  return gesture<ViewType>{std::forward<ViewType>(v),
                           std::forward<gesture_holder<TupleType>>(wrapped).elem};
}

template <class... FunctionTypes>
inline constexpr decltype(auto) gestured(FunctionTypes &&...funcs) {
  return gesture_holder{std::make_tuple(std::forward<FunctionTypes>(funcs)...)};
}
} // namespace usagi::ui
