お嬢様専用でしてよ。

ケツの穴から手ェ突っ込んで、奥歯型々させたりますわ〜!

# usagi
usagi は ui を concepts で表現したりする header-only なライブラリですわ〜！

# usagi no usage
iPlug2 での連携は [Pararaised](https://github.com/SachiSakurane/Pararaised) をご覧くださいまし。

base_view に描画とクリックイベントを追加する例ですわ。
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
      [](usagi::wrapper::icontrol::iplug_traits::mouse_traits::on_down_type mouse, auto &v)
      {
        // click
        if (usagi::geometry::contain(v.frame(), traits_type::point_type{mouse.x, mouse.y}))
          std::cout << "tapped" << std::endl;
      }));
```
