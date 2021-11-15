ﾝｻｷﾞ

# usagi

usagi は ui を concepts で表現したりする header-only なライブラリ

# usagi no usage

base_view に描画とクリックイベントを追加する例

```C++
auto &view = local_view.add_sub_view(
  usagi::wrapper::icontrol::iplug_traits::base_view_type{usagi::geometry::padding(local_view.frame(), 16.f)} |
  usagi::ui::surfaced(
      [](auto &context, const auto &v)
      {
        // draw
        SkAutoCanvasRestore restore{&context, true};
        context.saveLayer(nullptr, nullptr);

        SkPaint paint;
        paint.setColor(SK_ColorCYAN);
        context.drawRect(usagi::wrapper::skia::to_rect(v.frame()), paint);
      }) |
  usagi::ui::gestured(
      [](usagi::wrapper::icontrol::iplug_traits::gesture_traits::on_down_type gesture, auto &v)
      {
        // click
        if (usagi::geometry::contain(v.frame(), traits_type::point_type{gesture.x, gesture.y}))
          std::cout << "tapped" << std::endl;
      }));
```
