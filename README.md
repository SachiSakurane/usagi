ﾝｻｷﾞ

# usagi

usagi は UI を concepts で表現する header-only なライブラリです。

# usagi no usage

`view_stack` に child view を追加し、描画とクリックイベントを付ける例です。

```cpp
using value_type = float;
using gesture_parameter_type = usagi::type::gesture_parameter<value_type>;
using base_view_type = usagi::ui::base_view<value_type, DrawContext, gesture_parameter_type>;
using view_stack_type = usagi::ui::view_stack<value_type, DrawContext, gesture_parameter_type>;

auto local_view = view_stack_type{
    usagi::geometry::rect<value_type>{0.f, 0.f, 320.f, 240.f}};

auto decorated_child =
    base_view_type{usagi::geometry::rect<value_type>{16.f, 16.f, 120.f, 48.f}} |
    usagi::ui::surfaced(usagi::ui::on_draw(
        [](auto &context, auto offset, const auto &view) {
          // draw
          // `offset` is the accumulated placed origin from the root.
          // `view.frame()` is in the parent coordinate system.
          // `view.bounds()` is the view-local size.
        })) |
    usagi::ui::gestured(usagi::ui::on_down(
        [](auto gesture, auto offset, auto &view) {
          // gesture.position is local to `view`.
          // view_stack already performs child hit testing before dispatch.
          std::cout << "tapped" << std::endl;
          return true;
        }));

auto child_key =
    local_view.add_child_view(usagi::ui::make_view<decltype(decorated_child)>(
        std::move(decorated_child)));

local_view.bring_child_to_front(child_key);
```

`add_child_view` は child の key を返します。あとから child を参照・削除・
z-order 変更する場合は、その key を使います。

```cpp
auto &child = local_view.get_child_view(child_key);
local_view.send_child_to_back(child_key);
local_view.remove_child_view(child_key);
```

座標・描画仕様の詳細は
[`docs/ui-coordinate-and-drawing.md`](docs/ui-coordinate-and-drawing.md)
を参照してください。
