#pragma once

#include <iterator>
#include <memory>

#include <usagi/ui/base_view.hpp>

namespace usagi::ui {
/**
 * viewable を格納する型
 */
template <usagi::utility::arithmetic ValueType, class DrawContextType, class MouseParameterType>
class view {
  template <usagi::concepts::ui::viewable ViewType>
  class view_holder final
      : public usagi::ui::base_view<ValueType, DrawContextType, MouseParameterType> {
    using base_view_type =
        typename usagi::ui::base_view<ValueType, DrawContextType, MouseParameterType>;

  public:
    using rect_type = typename base_view_type::rect_type;
    using size_type = typename base_view_type::size_type;
    using draw_context_type = typename base_view_type::draw_context_type;
    using mouse_parameter_type = typename base_view_type::mouse_parameter_type;
    using mouse_traits = typename base_view_type::mouse_traits;
    using view_type = typename base_view_type::view_type;

    using children_type = typename base_view_type::children_type;
    using children_key_type = typename base_view_type::children_key_type;
    using children_mapped_type = typename base_view_type::children_mapped_type;
    using children_value_type = typename base_view_type::children_value_type;

    explicit view_holder(const ViewType &v) : holder{v} {}
    explicit view_holder(ViewType &&v) : holder{std::move(v)} {}

    view_holder(view_holder &&) noexcept = default;
    view_holder &operator=(view_holder &&) noexcept = default;

    void draw(draw_context_type &d) override { holder.draw(d); }

    size_type bounds() const override { return holder.bounds(); }
    rect_type frame() const override { return holder.frame(); }

    void event(typename mouse_traits::on_down_type mouse) override { holder.event(mouse); }
    void event(typename mouse_traits::on_drag_type mouse) override { holder.event(mouse); }
    void event(typename mouse_traits::on_up_type mouse) override { holder.event(mouse); }
    void event(typename mouse_traits::on_over_type mouse) override { holder.event(mouse); }
    void event(typename mouse_traits::on_out_type mouse) override { holder.event(mouse); }
    void event(typename mouse_traits::on_double_click_type mouse) override { holder.event(mouse); }

    void set_mouse_down(bool flag) override { holder.set_mouse_down(flag); }
    void set_mouse_over(bool flag) override { holder.set_mouse_over(flag); }
    [[nodiscard]] bool is_mouse_downed() const override { return holder.is_mouse_downed(); }
    [[nodiscard]] bool is_mouse_overed() const override { return holder.is_mouse_overed(); }

    children_value_type &add_sub_view(children_mapped_type &&sub_view) override {
      return holder.add_sub_view(std::forward<children_mapped_type>(sub_view));
    }

    children_mapped_type &get_sub_view(children_key_type index) override {
      return holder.get_sub_view(index);
    }

    bool remove_sub_view(children_key_type index) override { return holder.remove_sub_view(index); }

    [[nodiscard]] size_t sub_view_size() const override { return holder.sub_view_size(); }

    void set_enabled(bool flag) override { holder.set_enabled(flag); }
    [[nodiscard]] bool is_enabled() const override { return holder.is_enabled(); }

  private:
    ViewType holder;
  };

public:
  using value_type = ValueType;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = DrawContextType;
  using mouse_parameter_type = MouseParameterType;
  using mouse_traits = typename usagi::type::mouse_traits<mouse_parameter_type>;
  using view_type = usagi::ui::view<value_type, draw_context_type, mouse_parameter_type>;

  using children_mapped_type = view_type;
  using children_key_type = size_t;
  using children_type = std::map<children_key_type, children_mapped_type>;
  using children_value_type = typename children_type::value_type;

  view() : holder{nullptr} {}

  template <usagi::concepts::ui::viewable ViewType>
  view(ViewType &&v) : holder{std::make_unique<view_holder<ViewType>>(std::forward<ViewType>(v))} {}

  view(view &&) noexcept = default;
  view &operator=(view &&) noexcept = default;

  void draw(draw_context_type &d) { holder->draw(d); }

  size_type bounds() const { return holder->bounds(); }
  rect_type frame() const { return holder->frame(); }

  void event(typename mouse_traits::on_down_type mouse) { holder->event(mouse); }
  void event(typename mouse_traits::on_drag_type mouse) { holder->event(mouse); }
  void event(typename mouse_traits::on_up_type mouse) { holder->event(mouse); }
  void event(typename mouse_traits::on_over_type mouse) { holder->event(mouse); }
  void event(typename mouse_traits::on_out_type mouse) { holder->event(mouse); }
  void event(typename mouse_traits::on_double_click_type mouse) { holder->event(mouse); }

  void set_mouse_down(bool flag) { holder->set_mouse_down(flag); }
  void set_mouse_over(bool flag) { holder->set_mouse_over(flag); }
  [[nodiscard]] bool is_mouse_downed() const { return holder->is_mouse_downed(); }
  [[nodiscard]] bool is_mouse_overed() const { return holder->is_mouse_overed(); }

  children_value_type &add_sub_view(children_mapped_type &&sub_view) {
    return holder->add_sub_view(std::forward<children_mapped_type>(sub_view));
  }

  children_mapped_type &get_sub_view(children_key_type index) {
    return holder->get_sub_view(index);
  }

  bool remove_sub_view(children_key_type index) { return holder->remove_sub_view(index); }

  [[nodiscard]] size_t sub_view_size() const { return holder->sub_view_size(); }

  void set_enabled(bool flag) { holder->set_enabled(flag); }
  [[nodiscard]] bool is_enabled() const { return holder->is_enabled(); }

  explicit operator bool() const { return holder.operator bool(); }

private:
  std::unique_ptr<usagi::ui::base_view<value_type, draw_context_type, mouse_parameter_type>> holder;
};

template <usagi::concepts::ui::viewable ViewType>
view(const ViewType &) -> view<typename ViewType::value_type, typename ViewType::draw_context_type,
                               typename ViewType::mouse_parameter_type>;

template <usagi::concepts::ui::viewable ViewType>
view(ViewType &&) -> view<typename ViewType::value_type, typename ViewType::draw_context_type,
                          typename ViewType::mouse_parameter_type>;

template <usagi::concepts::ui::viewable ViewType, class... Args>
inline constexpr decltype(auto) make_view(Args &&...args) {
  return usagi::ui::view{ViewType{std::forward<Args>(args)...}};
}
} // namespace usagi::ui
