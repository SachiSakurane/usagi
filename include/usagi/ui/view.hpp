#pragma once

#include <memory>
#include <vector>

#include <usagi/concepts/geometry.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/geometry/geometry_traits.hpp>
#include <usagi/geometry/rect/function.hpp>
#include <usagi/type/mouse.hpp>
#include <usagi/utility/arithmetic.hpp>

namespace usagi::ui {
template <usagi::utility::arithmetic ValueType,
          usagi::concepts::graphics::draw_contextable DrawContextType>
class base_view {
public:
  using value_type = ValueType;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = DrawContextType;
  using mouse_traits = typename usagi::type::mouse_traits<value_type>;
  using view_type = usagi::ui::view<value_type, draw_context_type>;

  constexpr base_view() = default;
  constexpr explicit base_view(const usagi::concepts::geometry::size_concept auto &size)
      : content{size} {}
  constexpr base_view(const usagi::concepts::geometry::point_concept auto &point,
                      const usagi::concepts::geometry::size_concept auto &size)
      : content{point, size} {}
  constexpr explicit base_view(const usagi::concepts::geometry::rect_concept auto &frame)
      : content{frame} {}

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
    if (usagi::geometry::contain(frame(), point_type{mouse.x, mouse.y}))
      for (auto &child : children)
        child.event(mouse);
  }

  virtual void event(typename mouse_traits::on_up_type mouse) {
    if (usagi::geometry::contain(frame(), point_type{mouse.x, mouse.y}))
      for (auto &child : children)
        child.event(mouse);
  }

  virtual void event(typename mouse_traits::on_over_type mouse) {
    if (usagi::geometry::contain(frame(), point_type{mouse.x, mouse.y}))
      for (auto &child : children)
        child.event(mouse);
  }

  virtual view_type &add_sub_view(view_type &&sub_view) {
    return children.emplace_back(std::move(sub_view));
  }

private:
  rect_type content{};
  std::vector<view_type> children;
};

/**
 * view コンセプトを満たす型を格納する型
 */
template <usagi::utility::arithmetic ValueType,
          usagi::concepts::graphics::draw_contextable DrawContextType>
class view {
  template <usagi::concepts::ui::viewable ViewType>
  class view_holder final : public usagi::ui::base_view<ValueType, DrawContextType> {
    using base_view_type = typename usagi::ui::base_view<ValueType, DrawContextType>;

  public:
    using rect_type = typename base_view_type::rect_type;
    using size_type = typename base_view_type::size_type;
    using draw_context_type = typename base_view_type::draw_context_type;
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

    view_type &add_sub_view(view_type &&sub_view) override {
      return holder.add_sub_view(std::forward<view_type>(sub_view));
    }

  private:
    ViewType holder;
  };

public:
  using value_type = ValueType;
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  using draw_context_type = DrawContextType;
  using mouse_traits = typename usagi::type::mouse_traits<value_type>;
  using view_type = usagi::ui::view<value_type, draw_context_type>;

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

  view_type &add_sub_view(view_type &&sub_view) {
    return holder->add_sub_view(std::forward<view_type>(sub_view));
  }

  explicit operator bool() const { return holder.operator bool(); }

private:
  std::unique_ptr<usagi::ui::base_view<value_type, draw_context_type>> holder;
};

template <usagi::concepts::ui::viewable ViewType>
view(const ViewType &) -> view<typename ViewType::value_type, typename ViewType::draw_context_type>;

template <usagi::concepts::ui::viewable ViewType>
view(ViewType &&) -> view<typename ViewType::value_type, typename ViewType::draw_context_type>;
} // namespace usagi::ui
