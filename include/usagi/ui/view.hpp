#pragma once

#include <iterator>
#include <memory>
#include <vector>

#include <usagi/concepts/geometry.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/geometry/rect/function.hpp>
#include <usagi/type/mouse.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::ui {
template <usagi::utility::arithmetic ValueType, class DrawContextType, class MouseParameterType>
class base_view {
public:
  using value_type = ValueType;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = DrawContextType;
  using mouse_parameter_type = MouseParameterType;
  using mouse_traits = typename usagi::type::mouse_traits<mouse_parameter_type>;
  using view_type = usagi::ui::view<value_type, draw_context_type, mouse_parameter_type>;

  base_view() = default;
  explicit base_view(const usagi::concepts::geometry::rect_concept auto &frame) : content{frame} {}

  base_view(base_view &&) noexcept = default;
  base_view &operator=(base_view &&) noexcept = default;

  virtual ~base_view() = default;

  virtual void draw(draw_context_type &context) {
    for (auto &child : children) {
      child.draw(context);
    }
  }

  virtual size_type bounds() const { return content.size(); }
  virtual rect_type frame() const { return content; }

  virtual void event(typename mouse_traits::on_down_type mouse) {
    if (usagi::geometry::contain(frame(), point_type{mouse.x, mouse.y}))
      for (auto &child : children)
        child.event(mouse);
  }

  virtual void event(typename mouse_traits::on_drag_type mouse) {
    for (auto &child : children)
      child.event(mouse);
  }

  virtual void event(typename mouse_traits::on_up_type mouse) {
    for (auto &child : children)
      child.event(mouse);
  }

  virtual void event(typename mouse_traits::on_over_type mouse) {
    if (usagi::geometry::contain(frame(), point_type{mouse.x, mouse.y}))
      for (auto &child : children)
        child.event(mouse);
  }

  virtual void event(typename mouse_traits::on_out_type mouse) {
    for (auto &child : children)
      child.event(mouse);
  }

  virtual void event(typename mouse_traits::on_double_click_type mouse) {
    for (auto &child : children)
      child.event(mouse);
  }

  virtual view_type &add_sub_view(view_type &&sub_view) {
    return children.emplace_back(std::forward<view_type>(sub_view));
  }

  virtual bool remove_sub_view(size_t index) {
    if (index < children.size()) {
      auto it = std::begin(children);
      std::advance(it, index);
      if (it != std::end(children)) {
        children.erase(it);
        return true;
      }
    }
    return false;
  }

  [[nodiscard]] virtual size_t sub_view_size() const { return children.size(); }

private:
  rect_type content{};
  std::vector<view_type> children;
};

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

    view_type &add_sub_view(view_type &&sub_view) override {
      return holder.add_sub_view(std::forward<view_type>(sub_view));
    }

    bool remove_sub_view(size_t index) override { return holder.remove_sub_view(index); }

    [[nodiscard]] size_t sub_view_size() const override { return holder.sub_view_size(); }

  private:
    ViewType holder;
  };

public:
  using value_type = ValueType;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = DrawContextType;
  using mouse_parameter_type = MouseParameterType;
  using mouse_traits = typename usagi::type::mouse_traits<mouse_parameter_type>;
  using view_type = usagi::ui::view<value_type, draw_context_type, mouse_parameter_type>;

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

  view_type &add_sub_view(view_type &&sub_view) {
    return holder->add_sub_view(std::forward<view_type>(sub_view));
  }

  bool remove_sub_view(size_t index) { return holder->remove_sub_view(index); }

  [[nodiscard]] size_t sub_view_size() const { return holder->sub_view_size(); }

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
