#pragma once

#include <iterator>
#include <memory>

#include <usagi/ui/base_view.hpp>

namespace usagi::ui {
template <usagi::concepts::ui::viewable ViewType>
class view_holder final : public usagi::ui::base_view<typename ViewType::value_type,
                                                      typename ViewType::draw_context_type,
                                                      typename ViewType::gesture_parameter_type> {
  using base_view_type = typename usagi::ui::base_view<typename ViewType::value_type,
                                                       typename ViewType::draw_context_type,
                                                       typename ViewType::gesture_parameter_type>;

public:
  using rect_type = typename base_view_type::rect_type;
  using size_type = typename base_view_type::size_type;
  using draw_context_type = typename base_view_type::draw_context_type;
  using gesture_parameter_type = typename base_view_type::gesture_parameter_type;
  using gesture_traits = typename base_view_type::gesture_traits;

  template <class... Args>
  explicit view_holder(Args &&...args) : holder{std::forward<Args>(args)...} {}

  constexpr view_holder(view_holder &&) noexcept = default;
  view_holder &operator=(view_holder &&) noexcept = default;

  void draw(draw_context_type &d) override { holder.draw(d); }

  size_type bounds() const override { return holder.bounds(); }
  rect_type frame() const override { return holder.frame(); }

  bool event(typename gesture_traits::on_down_type parameter) override {
    return holder.event(parameter);
  }
  void event(typename gesture_traits::on_drag_type parameter) override { holder.event(parameter); }
  void event(typename gesture_traits::on_up_type parameter) override { holder.event(parameter); }
  bool event(typename gesture_traits::on_over_type parameter) override {
    return holder.event(parameter);
  }
  void event(typename gesture_traits::on_out_type parameter) override { holder.event(parameter); }
  bool event(typename gesture_traits::on_double_type parameter) override {
    return holder.event(parameter);
  }
  bool event(typename gesture_traits::on_wheel_type parameter) override {
    return holder.event(parameter);
  }

  void set_down(bool flag) override { holder.set_down(flag); }
  void set_over(bool flag) override { holder.set_over(flag); }
  [[nodiscard]] bool on_downed() const override { return holder.on_downed(); }
  [[nodiscard]] bool on_overed() const override { return holder.on_overed(); }

  void set_enabled(bool flag) override { holder.set_enabled(flag); }
  [[nodiscard]] bool is_enabled() const override { return holder.is_enabled(); }

private:
  ViewType holder;
};

/**
 * viewable を格納する型
 */
template <usagi::concepts::arithmetic ValueType, class DrawContextType, class GestureParameterType>
class view final {
  using base_view_type =
      typename usagi::ui::base_view<ValueType, DrawContextType, GestureParameterType>;

public:
  using value_type = ValueType;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = DrawContextType;
  using gesture_parameter_type = GestureParameterType;
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  constexpr view() = default;
  explicit view(std::unique_ptr<base_view_type> &&v) : holder{std::move(v)} {}

  view(view &&) noexcept = default;
  view &operator=(view &&) noexcept = default;

  void draw(draw_context_type &d) { holder->draw(d); }

  size_type bounds() const { return holder->bounds(); }
  rect_type frame() const { return holder->frame(); }

  bool event(typename gesture_traits::on_down_type parameter) { return holder->event(parameter); }
  void event(typename gesture_traits::on_drag_type parameter) { holder->event(parameter); }
  void event(typename gesture_traits::on_up_type parameter) { holder->event(parameter); }
  bool event(typename gesture_traits::on_over_type parameter) { return holder->event(parameter); }
  void event(typename gesture_traits::on_out_type parameter) { holder->event(parameter); }
  bool event(typename gesture_traits::on_double_type parameter) { return holder->event(parameter); }
  bool event(typename gesture_traits::on_wheel_type parameter) { return holder->event(parameter); }

  void set_down(bool flag) { holder->set_down(flag); }
  void set_over(bool flag) { holder->set_over(flag); }
  [[nodiscard]] bool on_downed() const { return holder->on_downed(); }
  [[nodiscard]] bool on_overed() const { return holder->on_overed(); }

  void set_enabled(bool flag) { holder->set_enabled(flag); }
  [[nodiscard]] bool is_enabled() const { return holder->is_enabled(); }

  explicit operator bool() const { return holder.operator bool(); }

private:
  std::unique_ptr<base_view_type> holder{nullptr};
};

template <usagi::concepts::ui::viewable ViewType>
view(const ViewType &) -> view<typename ViewType::value_type, typename ViewType::draw_context_type,
                               typename ViewType::gesture_parameter_type>;

template <usagi::concepts::ui::viewable ViewType>
view(ViewType &&) -> view<typename ViewType::value_type, typename ViewType::draw_context_type,
                          typename ViewType::gesture_parameter_type>;

template <usagi::concepts::ui::viewable ViewType, class... Args>
inline decltype(auto) make_view(Args &&...args) {
  return usagi::ui::view<typename ViewType::value_type, typename ViewType::draw_context_type,
                         typename ViewType::gesture_parameter_type>{
      std::make_unique<view_holder<ViewType>>(std::forward<Args>(args)...)};
}
} // namespace usagi::ui
