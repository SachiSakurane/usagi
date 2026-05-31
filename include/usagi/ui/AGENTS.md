# UI Instructions

## Surface Draw Handlers

`usagi::ui::surface` draw handlers are observational decorators. `on_draw`
callbacks must be invocable with:

```cpp
draw_context_type &, offset_type, const ViewType &
```

Do not require mutable access to the wrapped view from an `on_draw` callback.
If a behavior needs to mutate view state, model it outside the surface draw
handler path.
