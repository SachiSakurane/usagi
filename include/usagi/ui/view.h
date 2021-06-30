#pragma once

#include <memory>
#include <vector>

#include <usagi/concepts/ui/viewable.h>
#include <usagi/geometry/geometry_traits.h>
#include <usagi/type/mouse.h>

namespace usagi::ui
{
  template <
      class ValueType,
      usagi::concepts::graphics::draw_contextable DrawContextType>
  class base_view
  {
  public:
    using value_type = ValueType;
    using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
    using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
    using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
    using draw_context_type = DrawContextType;
    using mouse_traits = typename usagi::type::mouse::mouse_traits<value_type>;
    using view_type = usagi::ui::view<value_type, draw_context_type>;

    constexpr base_view() = default;
    constexpr explicit base_view(const size_type &size) : content{size} {}
    constexpr base_view(const point_type &point, const size_type &size) : content{point, size} {}

    virtual void draw(draw_context_type &)
    {
    }

    virtual size_type bounds() const { return content.size(); }
    virtual rect_type frame() const { return content; }

    virtual void event(typename mouse_traits::on_down_type) {}
    virtual void event(typename mouse_traits::on_drag_type) {}
    virtual void event(typename mouse_traits::on_up_type) {}
    virtual void event(typename mouse_traits::on_over_type) {}

    virtual view_type &add_sub_view(view_type &&sub_view)
    {
      return children.emplace_back(std::move(sub_view));
    }

  private:
    rect_type content{};
    std::vector<view_type> children;
  };

  /**
   * view コンセプトを満たす型を格納する型
   */
  template <
      class ValueType,
      usagi::concepts::graphics::draw_contextable DrawContextType>
  class view
  {
    template <usagi::concepts::ui::viewable ViewType>
    class view_holder final : usagi::ui::base_view<ValueType, DrawContextType>
    {
      using base_view_type = typename usagi::ui::base_view<ValueType, DrawContextType>;

    public:
      using rect_type = typename base_view_type::rect_type;
      using size_type = typename base_view_type::size_type;
      using draw_context_type = typename base_view_type::DrawContextType;
      using mouse_traits = typename base_view_type::mouse_traits;
      using view_type = typename base_view_type::view_type;

      view_holder(const ViewType &v) : holder{v} {}
      view_holder(ViewType &&v) : holder{std::move(v)} {}

      void draw(draw_context_type &d) override { holder.draw(d); }

      size_type bounds() const override { return holder.bounds(); }
      rect_type frame() const override { return holder.frame(); }

      void event(typename mouse_traits::on_down_type mouse) override { holder.event(mouse); }
      void event(typename mouse_traits::on_drag_type mouse) override { holder.event(mouse); }
      void event(typename mouse_traits::on_up_type mouse) override { holder.event(mouse); }
      void event(typename mouse_traits::on_over_type mouse) override { holder.event(mouse); }

      view_type &add_sub_view(view_type &&sub_view)
      {
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
    using mouse_traits = typename usagi::type::mouse::mouse_traits<value_type>;
    using view_type = usagi::ui::view<value_type, draw_context_type>;

    template <usagi::concepts::ui::viewable ViewType>
    view(const ViewType &v) : holder{std::make_unique<view_holder<ViewType>>(v)} {}

    template <usagi::concepts::ui::viewable ViewType>
    view(ViewType &&v) : holder{std::make_unique<view_holder<ViewType>>(std::move(v))} {}

    void draw(draw_context_type &d) { holder->draw(d); }

    size_type bounds() const { return holder->bounds(); }
    rect_type frame() const { return holder->frame(); }

    void event(typename mouse_traits::on_down_type mouse) { holder->event(mouse); }
    void event(typename mouse_traits::on_drag_type mouse) { holder->event(mouse); }
    void event(typename mouse_traits::on_up_type mouse) { holder->event(mouse); }
    void event(typename mouse_traits::on_over_type mouse) { holder->event(mouse); }

    view_type &add_sub_view(view_type &&sub_view)
    {
      return holder->add_sub_view(std::forward<view_type>(sub_view));
    }

  private:
    std::unique_ptr<view_type> holder;
  };
}
