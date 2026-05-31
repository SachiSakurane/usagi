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

## View Moved-From State

`usagi::ui::view` is a non-null owning handle during normal use. A moved-from
`view` may be empty; only destruction, assignment, `has_view()`, and
`operator bool()` are valid on a moved-from `view`.

Do not call `draw`, `event`, `bounds`, `frame`, state accessors, or mutators on
a moved-from `view`.

Use `has_view()` / `operator bool()` only to inspect whether a `view` still owns
an implementation, primarily after move operations. Do not model optional UI
nodes with empty `view`.
