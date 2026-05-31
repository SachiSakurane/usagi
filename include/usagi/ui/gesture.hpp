#pragma once

#include <functional>
#include <tuple>
#include <utility>

#include <usagi/concepts/ui/gesture_handler.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/ui/gesture_handler.hpp>

namespace usagi::ui {
namespace detail {
  template <class Tag, class... Args>
  struct pick_handler;

  template <class Tag, class Front, class... Args>
  struct pick_handler<Tag, Front, Args...> : pick_handler<Tag, Args...> {
    pick_handler<Tag, Front, Args...>(Front &&, Args &&...args)
        : pick_handler<Tag, Args...>{std::forward<Args>(args)...} {}
  };

  template <class Tag, usagi::concepts::ui::gesture_handler_for<Tag> Front, class... Args>
  struct pick_handler<Tag, Front, Args...> {
    pick_handler<Tag, Front, Args...>(Front &&handler, Args &&...)
        : elem{std::forward<Front>(handler).func} {}

    typename std::remove_cvref_t<Front>::function_type elem;
  };

  template <class Tag>
  struct pick_handler<Tag> {
    explicit pick_handler<Tag>() {}
    std::nullptr_t elem{nullptr};
  };

  template <class Tag, class... Args>
  inline constexpr decltype(auto) pick_handler_wrapper(Args &&...args) {
    return pick_handler<Tag, Args...>{std::forward<Args>(args)...}.elem;
  }

  template <class Tag, class Tuple, std::size_t... Sequence>
  inline constexpr decltype(auto) pick_tagged_handler_impl(Tuple &&t,
                                                          std::index_sequence<Sequence...>) {
    return pick_handler_wrapper<Tag>(
        std::forward<std::tuple_element_t<Sequence, Tuple>>(std::get<Sequence>(t))...);
  }

  template <class Tag, class CandidatesTuple>
  inline constexpr decltype(auto) pick_tagged_handler(CandidatesTuple t) {
    return pick_tagged_handler_impl<Tag>(
        std::forward<CandidatesTuple>(t),
        std::make_index_sequence<std::tuple_size_v<CandidatesTuple>>());
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
  using gesture_traits =
      typename usagi::type::gesture_traits<typename ViewType::gesture_parameter_type>;

  template <class TupleType>
  explicit gestures(TupleType t)
      : on_down_holder{usagi::ui::detail::pick_tagged_handler<usagi::ui::detail::on_down_tag>(t)},
        on_drag_holder{usagi::ui::detail::pick_tagged_handler<usagi::ui::detail::on_drag_tag>(t)},
        on_up_holder{usagi::ui::detail::pick_tagged_handler<usagi::ui::detail::on_up_tag>(t)},
        on_over_holder{usagi::ui::detail::pick_tagged_handler<usagi::ui::detail::on_over_tag>(t)},
        on_out_holder{usagi::ui::detail::pick_tagged_handler<usagi::ui::detail::on_out_tag>(t)},
        on_double_holder{
            usagi::ui::detail::pick_tagged_handler<usagi::ui::detail::on_double_tag>(t)},
        on_wheel_holder{
            usagi::ui::detail::pick_tagged_handler<usagi::ui::detail::on_wheel_tag>(t)} {}

  std::function<bool(typename gesture_traits::on_down_type, typename gesture_traits::offset_type, ViewType &)> on_down_holder;
  std::function<void(typename gesture_traits::on_drag_type, typename gesture_traits::offset_type, ViewType &)> on_drag_holder;
  std::function<void(typename gesture_traits::on_up_type, typename gesture_traits::offset_type, ViewType &)> on_up_holder;
  std::function<bool(typename gesture_traits::on_over_type, typename gesture_traits::offset_type, ViewType &)> on_over_holder;
  std::function<void(typename gesture_traits::on_out_type, typename gesture_traits::offset_type, ViewType &)> on_out_holder;
  std::function<bool(typename gesture_traits::on_double_type, typename gesture_traits::offset_type, ViewType &)> on_double_holder;
  std::function<bool(typename gesture_traits::on_wheel_type, typename gesture_traits::offset_type, ViewType &)> on_wheel_holder;
};

template <usagi::concepts::ui::viewable ViewType>
struct gesture {
  using value_type = typename ViewType::value_type;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = typename ViewType::draw_context_type;
  using offset_type = typename ViewType::offset_type;
  using gesture_parameter_type = typename ViewType::gesture_parameter_type;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  template <class TupleType>
  gesture(ViewType &&v, TupleType &&t) : holder{std::move(v)}, g{std::forward<TupleType>(t)} {}

  void draw(draw_context_type &context, offset_type offset) { holder.draw(context, offset); }

  size_type bounds() const { return holder.bounds(); }
  rect_type frame() const { return holder.frame(); }

  bool event(typename gesture_traits::on_down_type parameter, offset_type offset) {
    if (g.on_down_holder) {
      if (g.on_down_holder(parameter, offset, holder)) {
        return true;
      }
    }
    return holder.event(parameter, offset);
  }

  void event(typename gesture_traits::on_drag_type parameter, offset_type offset) {
    if (g.on_drag_holder) {
      g.on_drag_holder(parameter, offset, holder);
    }
    holder.event(parameter, offset);
  }

  void event(typename gesture_traits::on_up_type parameter, offset_type offset) {
    if (g.on_up_holder) {
      g.on_up_holder(parameter, offset, holder);
    }
    holder.event(parameter, offset);
  }

  bool event(typename gesture_traits::on_over_type parameter, offset_type offset) {
    if (g.on_over_holder) {
      if (g.on_over_holder(parameter, offset, holder)) {
        return true;
      }
    }
    return holder.event(parameter, offset);
  }

  void event(typename gesture_traits::on_out_type parameter, offset_type offset) {
    if (g.on_out_holder) {
      g.on_out_holder(parameter, offset, holder);
    }
    holder.event(parameter, offset);
  }

  bool event(typename gesture_traits::on_double_type parameter, offset_type offset) {
    if (g.on_double_holder) {
      if (g.on_double_holder(parameter, offset, holder)) {
        return true;
      }
    }
    return holder.event(parameter, offset);
  }

  bool event(typename gesture_traits::on_wheel_type parameter, offset_type offset) {
    if (g.on_wheel_holder) {
      if (g.on_wheel_holder(parameter, offset, holder)) {
        return true;
      }
    }
    return holder.event(parameter, offset);
  }

  void set_down(bool flag) { holder.set_down(flag); }
  void set_over(bool flag) { holder.set_over(flag); }
  [[nodiscard]] bool is_downed() const { return holder.is_downed(); }
  [[nodiscard]] bool is_overed() const { return holder.is_overed(); }

  void set_enabled(bool flag) { holder.set_enabled(flag); }
  [[nodiscard]] bool is_enabled() const { return holder.is_enabled(); }

private:
  ViewType holder;
  gestures<ViewType> g;
};

template <usagi::concepts::ui::viewable ViewType,
          usagi::concepts::ui::gesture_tuple_requirement<ViewType> TupleType>
inline constexpr decltype(auto) operator|(ViewType &&v, gesture_holder<TupleType> &&wrapped) {
  return gesture<ViewType>{std::forward<ViewType>(v),
                           std::forward<gesture_holder<TupleType>>(wrapped).elem};
}

template <class... FunctionTypes>
inline constexpr decltype(auto) gestured(FunctionTypes &&...funcs) {
  return gesture_holder{std::make_tuple(std::forward<FunctionTypes>(funcs)...)};
}
} // namespace usagi::ui
