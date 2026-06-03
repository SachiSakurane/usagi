# UI Coordinate And Drawing Specification

This document defines the coordinate and drawing behavior used by `usagi::ui`
views.

## View Geometry

- `frame()` is a view rectangle in its parent coordinate system.
- `bounds()` is a view size in the view-local coordinate system.
- `transform()` is applied after frame placement.
- `translation()` is post-layout movement in the parent coordinate system.
- `rotation()` and `scale()` are applied around `transform().origin()` in the
  view-local coordinate system.

For a child view in a `view_stack`, the placed origin is:

```text
placed_origin = parent_offset + child.frame().origin + child.translation()
```

The accumulated placed origin is passed to drawing and events as `offset`.

## Drawing

`draw(context, offset)` receives the accumulated placed origin from the root.
Custom draw handlers should draw local content by using `offset` as the local
origin in the draw context.

`view_stack` draws children from back to front. It applies each child's draw
transform around:

```text
offset + child.transform().origin()
```

Translation is not applied as a draw-context transform; it is already included
in the accumulated `offset`. Scale and rotation are applied by draw context
adapters, such as the Skia adapter.

## Events

Gesture `position` is local to the receiving view.

`view_stack` receives stack-local gestures, hit-tests children against their
transformed bounds, and dispatches by converting the position through the
inverse child transform into child-local coordinates.

New hit-test events are clipped to the stack bounds by default. This affects
`on_down`, `on_over`, `on_double`, and `on_wheel`. `on_drag`, `on_up`, and
`on_out` continue to dispatch to already tracked children so state can be
cleaned up.

## Draw Clipping

Draw clipping is opt-in and disabled by default.

When `set_draw_clipping(true)` is enabled, `view_stack` clips child drawing to
its own placed bounds. The clip is applied outside child transforms:

```text
save
  clip stack placed bounds
  child scale/rotation transform
    draw child
restore
```

This is container `overflow: hidden` behavior. In the Skia adapter, clipping is
an intersecting rectangular `SkCanvas::clipRect`.
