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

## View Stack Child Removal

`usagi::ui::view_stack::remove_child_view` is a silent ownership operation. It
removes the child without dispatching synthetic gesture events such as `on_up`
or `on_out`.

If a child needs gesture cleanup before removal, dispatch the required event
explicitly before calling `remove_child_view`.

## View Stack Coordinates

`usagi::ui::view_stack` is a composite view of children only. It does not draw a
separate holder view.

For UI views:

- `frame()` is the view rectangle in the parent coordinate system.
- `bounds()` is the view size in the view-local coordinate system.
- `draw(..., offset)` receives the accumulated offset from the root.
- `event(..., offset)` receives a gesture whose `position` is local to the
  receiving view.

`view_stack` hit-tests children against `child.frame()` using the stack-local
gesture position. Before dispatching to a child, it converts
`gesture.position` to child-local coordinates and adds the child origin to the
draw/event offset.

## View Stack Event Clipping

`view_stack` clips new hit-test events to its own local bounds by default.

`set_event_clipping(false)` allows new hit-test events outside the stack bounds
to reach children. Clipping affects `on_down`, `on_over`, `on_double`, and
`on_wheel` hit testing. `on_drag`, `on_up`, and `on_out` continue to dispatch to
already tracked children so down/over state can be cleaned up.

## View Stack Draw Clipping

`view_stack` draw clipping is opt-in and disabled by default.

When `set_draw_clipping(true)` is enabled, `view_stack` clips child drawing to
its own placed bounds. The clip is applied outside child transforms: child
translation, scale, and rotation happen inside the stack bounds clip. Treat this
as container `overflow: hidden` behavior.

Skia uses an intersecting rectangular clip through `SkCanvas::clipRect`.

## View Stack Z-Order

`view_stack` child keys identify children; they are not z-order values.
Z-order is defined by the internal child order:

- children are drawn from back to front
- events are dispatched from front to back
- `bring_child_to_front` and `send_child_to_back` move keys in that order

Do not infer z-order from the numeric value of `child_view_key_type`.
