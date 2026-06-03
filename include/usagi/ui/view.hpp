#pragma once

#include <cassert>
#include <memory>
#include <utility>

#include <usagi/concepts/floating_point.hpp>
#include <usagi/concepts/ui/transformable.hpp>
#include <usagi/concepts/ui/viewable.hpp>
#include <usagi/ui/view_interface.hpp>

namespace usagi::ui {
namespace detail {
  /// Type-erased holder that forwards `view_interface` calls to a concrete view.
  ///
  /// @tparam ViewType Concrete viewable type stored by value.
  template <usagi::concepts::ui::viewable ViewType>
  requires usagi::concepts::ui::transformable<ViewType>
  class view_holder final
      : public usagi::ui::view_interface<typename ViewType::value_type,
                                         typename ViewType::draw_context_type,
                                         typename ViewType::gesture_parameter_type> {
    using view_interface_type =
        typename usagi::ui::view_interface<typename ViewType::value_type,
                                           typename ViewType::draw_context_type,
                                           typename ViewType::gesture_parameter_type>;

  public:
    /// Shared geometry value type.
    using value_type = typename view_interface_type::value_type;
    /// Point type exposed by the interface.
    using point_type = typename view_interface_type::point_type;
    /// Rectangle type exposed by the interface.
    using rect_type = typename view_interface_type::rect_type;
    /// Size type exposed by the interface.
    using size_type = typename view_interface_type::size_type;
    /// Transform type exposed by the interface.
    using transform_type = typename view_interface_type::transform_type;
    /// Mutable drawing context type.
    using draw_context_type = typename view_interface_type::draw_context_type;
    /// Draw and event offset type.
    using offset_type = typename view_interface_type::offset_type;
    /// Raw gesture parameter payload type.
    using gesture_parameter_type = typename view_interface_type::gesture_parameter_type;
    /// Gesture event type bundle.
    using gesture_traits = typename view_interface_type::gesture_traits;

    /// Creates a holder with a default-constructed concrete view.
    view_holder() = default;

    /// Creates a holder by forwarding arguments to the concrete view.
    ///
    /// @param args Arguments used to construct `ViewType`.
    template <class... Args>
    explicit view_holder(Args &&...args) : holder{std::forward<Args>(args)...} {}

    /// Forwards drawing to the concrete view.
    ///
    /// @param context Mutable drawing context.
    /// @param offset Accumulated offset from the root view.
    void draw(draw_context_type &context, offset_type offset) override {
      holder.draw(context, offset);
    }

    /// Returns the concrete view bounds.
    ///
    /// @return Bounds reported by the stored view.
    size_type bounds() const override { return holder.bounds(); }
    /// Returns the concrete view frame.
    ///
    /// @return Frame reported by the stored view.
    rect_type frame() const override { return holder.frame(); }

    bool event(typename gesture_traits::on_down_type parameter, offset_type offset) override {
      return holder.event(parameter, offset);
    }
    void event(typename gesture_traits::on_drag_type parameter, offset_type offset) override {
      holder.event(parameter, offset);
    }
    void event(typename gesture_traits::on_up_type parameter, offset_type offset) override {
      holder.event(parameter, offset);
    }
    bool event(typename gesture_traits::on_over_type parameter, offset_type offset) override {
      return holder.event(parameter, offset);
    }
    void event(typename gesture_traits::on_out_type parameter, offset_type offset) override {
      holder.event(parameter, offset);
    }
    bool event(typename gesture_traits::on_double_type parameter, offset_type offset) override {
      return holder.event(parameter, offset);
    }
    bool event(typename gesture_traits::on_wheel_type parameter, offset_type offset) override {
      return holder.event(parameter, offset);
    }

    void set_down(bool flag) override { holder.set_down(flag); }
    void set_over(bool flag) override { holder.set_over(flag); }
    [[nodiscard]] bool is_downed() const override { return holder.is_downed(); }
    [[nodiscard]] bool is_overed() const override { return holder.is_overed(); }

    void set_enabled(bool flag) override { holder.set_enabled(flag); }
    [[nodiscard]] bool is_enabled() const override { return holder.is_enabled(); }

    transform_type transform() const override { return holder.transform(); }
    void set_transform(transform_type t) override { holder.set_transform(t); }

    point_type translation() const override { return holder.translation(); }
    void set_translation(point_type p) override { holder.set_translation(p); }

    value_type rotation() const override { return holder.rotation(); }
    void set_rotation(value_type r) override { holder.set_rotation(r); }
    void set_rotation(value_type r, point_type origin) override {
      holder.set_rotation(r, origin);
    }

    point_type scale() const override { return holder.scale(); }
    void set_scale(point_type s) override { holder.set_scale(s); }
    void set_scale(point_type s, point_type origin) override { holder.set_scale(s, origin); }

  private:
    ViewType holder{};
  };
} // namespace detail

/// Move-only owning handle for a type-erased viewable object.
///
/// @tparam ValueType Floating-point geometry value type.
/// @tparam DrawContextType Mutable drawing context type.
/// @tparam GestureParameterType Raw gesture parameter payload type.
template <usagi::concepts::floating_point ValueType, class DrawContextType,
          class GestureParameterType>
class view final {
  using base_view_type =
      usagi::ui::view_interface<ValueType, DrawContextType, GestureParameterType>;

public:
  /// Shared geometry value type.
  using value_type = ValueType;
  /// Point type using `value_type`.
  using point_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  /// Rectangle type using `value_type`.
  using rect_type = typename usagi::geometry::geometry_traits<value_type>::rect_type;
  /// Size type using `value_type`.
  using size_type = typename usagi::geometry::geometry_traits<value_type>::size_type;
  /// Transform type using `value_type`.
  using transform_type = typename usagi::geometry::geometry_traits<value_type>::transform_type;
  /// Mutable drawing context type.
  using draw_context_type = DrawContextType;
  /// Draw and event offset type.
  using offset_type = typename usagi::geometry::geometry_traits<value_type>::point_type;
  /// Raw gesture parameter payload type.
  using gesture_parameter_type = GestureParameterType;
  /// Gesture event type bundle.
  using gesture_traits = typename usagi::type::gesture_traits<gesture_parameter_type>;

  view() = delete;

  /// Creates a view handle from an implementation pointer.
  ///
  /// @param v Non-null view implementation pointer.
  explicit view(std::unique_ptr<base_view_type> &&v) : holder{std::move(v)} { assert(holder); }

  /// Moves a view handle.
  view(view &&) noexcept = default;
  /// Move-assigns a view handle.
  ///
  /// @return Reference to this view handle.
  view &operator=(view &&) noexcept = default;

  /// Draws the contained view.
  ///
  /// @param context Mutable drawing context.
  /// @param offset Accumulated offset from the root view.
  void draw(draw_context_type &context, offset_type offset) {
    assert(holder);
    holder->draw(context, offset);
  }

  /// Returns the contained view's local bounds size.
  ///
  /// @return Bounds reported by the contained view.
  size_type bounds() const {
    assert(holder);
    return holder->bounds();
  }
  /// Returns the contained view's frame in parent coordinates.
  ///
  /// @return Frame reported by the contained view.
  rect_type frame() const {
    assert(holder);
    return holder->frame();
  }

  /// Dispatches a down event to the contained view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the contained view consumes the event.
  bool event(typename gesture_traits::on_down_type parameter, offset_type offset) {
    assert(holder);
    return holder->event(parameter, offset);
  }
  /// Dispatches a drag event to the contained view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  void event(typename gesture_traits::on_drag_type parameter, offset_type offset) {
    assert(holder);
    holder->event(parameter, offset);
  }
  /// Dispatches an up event to the contained view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  void event(typename gesture_traits::on_up_type parameter, offset_type offset) {
    assert(holder);
    holder->event(parameter, offset);
  }
  /// Dispatches an over event to the contained view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the contained view consumes the event.
  bool event(typename gesture_traits::on_over_type parameter, offset_type offset) {
    assert(holder);
    return holder->event(parameter, offset);
  }
  /// Dispatches an out event to the contained view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  void event(typename gesture_traits::on_out_type parameter, offset_type offset) {
    assert(holder);
    holder->event(parameter, offset);
  }
  /// Dispatches a double-click event to the contained view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the contained view consumes the event.
  bool event(typename gesture_traits::on_double_type parameter, offset_type offset) {
    assert(holder);
    return holder->event(parameter, offset);
  }
  /// Dispatches a wheel event to the contained view.
  ///
  /// @param parameter Gesture parameter in this view's local coordinate system.
  /// @param offset Accumulated offset from the root view.
  /// @return `true` when the contained view consumes the event.
  bool event(typename gesture_traits::on_wheel_type parameter, offset_type offset) {
    assert(holder);
    return holder->event(parameter, offset);
  }

  /// Updates the contained view's active press state.
  ///
  /// @param flag New press-state value.
  void set_down(bool flag) {
    assert(holder);
    holder->set_down(flag);
  }
  /// Updates the contained view's pointer-over state.
  ///
  /// @param flag New over-state value.
  void set_over(bool flag) {
    assert(holder);
    holder->set_over(flag);
  }
  /// Returns whether the contained view is currently pressed.
  ///
  /// @return Current press-state value.
  [[nodiscard]] bool is_downed() const {
    assert(holder);
    return holder->is_downed();
  }
  /// Returns whether the pointer is currently over the contained view.
  ///
  /// @return Current over-state value.
  [[nodiscard]] bool is_overed() const {
    assert(holder);
    return holder->is_overed();
  }

  /// Updates whether the contained view participates in draw and event traversal.
  ///
  /// @param flag New enabled-state value.
  void set_enabled(bool flag) {
    assert(holder);
    holder->set_enabled(flag);
  }
  /// Returns whether the contained view is enabled.
  ///
  /// @return Current enabled-state value.
  [[nodiscard]] bool is_enabled() const {
    assert(holder);
    return holder->is_enabled();
  }

  /// Returns the contained view's layout-after transform.
  ///
  /// @return Transform reported by the contained view.
  [[nodiscard]] transform_type transform() const {
    assert(holder);
    return holder->transform();
  }
  /// Replaces the contained view's layout-after transform.
  ///
  /// @param t New transform value.
  void set_transform(transform_type t) {
    assert(holder);
    holder->set_transform(t);
  }

  /// Returns the contained view's transform translation.
  ///
  /// @return Translation applied after frame placement.
  [[nodiscard]] point_type translation() const {
    assert(holder);
    return holder->translation();
  }
  /// Updates the contained view's transform translation.
  ///
  /// @param p New translation value.
  void set_translation(point_type p) {
    assert(holder);
    holder->set_translation(p);
  }

  /// Returns the contained view's transform rotation.
  ///
  /// @return Current rotation angle in radians.
  [[nodiscard]] value_type rotation() const {
    assert(holder);
    return holder->rotation();
  }
  /// Updates the contained view's transform rotation without changing the current origin.
  ///
  /// @param r New rotation angle in radians.
  void set_rotation(value_type r) {
    assert(holder);
    holder->set_rotation(r);
  }
  /// Updates the contained view's transform rotation and transform origin together.
  ///
  /// @param r New rotation angle in radians.
  /// @param origin Origin used by the rotation operation.
  void set_rotation(value_type r, point_type origin) {
    assert(holder);
    holder->set_rotation(r, origin);
  }

  /// Returns the contained view's transform scale.
  ///
  /// @return Current x and y scale factors.
  [[nodiscard]] point_type scale() const {
    assert(holder);
    return holder->scale();
  }
  /// Updates the contained view's transform scale without changing the current origin.
  ///
  /// @param s New x and y scale factors.
  void set_scale(point_type s) {
    assert(holder);
    holder->set_scale(s);
  }
  /// Updates the contained view's transform scale and transform origin together.
  ///
  /// @param s New x and y scale factors.
  /// @param origin Origin used by the scale operation.
  void set_scale(point_type s, point_type origin) {
    assert(holder);
    holder->set_scale(s, origin);
  }

  /// Returns whether this handle currently owns a view implementation.
  ///
  /// @return `true` when a view implementation is present; otherwise `false`.
  [[nodiscard]] bool has_view() const { return holder.operator bool(); }
  /// Returns whether this handle currently owns a view implementation.
  ///
  /// @return `true` when a view implementation is present; otherwise `false`.
  explicit operator bool() const { return has_view(); }

private:
  std::unique_ptr<base_view_type> holder;
};

/// Creates a type-erased owning view from a concrete viewable type.
///
/// @tparam ViewType Concrete viewable type to store.
/// @tparam Args Constructor argument types for `ViewType`.
/// @param args Arguments forwarded to `ViewType`.
/// @return Owning `view` handle containing a `ViewType` instance.
template <usagi::concepts::ui::viewable ViewType, class... Args>
requires usagi::concepts::ui::transformable<ViewType>
inline decltype(auto) make_view(Args &&...args) {
  return usagi::ui::view<typename ViewType::value_type, typename ViewType::draw_context_type,
                         typename ViewType::gesture_parameter_type>{
      std::make_unique<detail::view_holder<ViewType>>(std::forward<Args>(args)...)};
}
} // namespace usagi::ui
