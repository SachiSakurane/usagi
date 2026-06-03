# Repository Manifest

## Test Source Scan Roots

When scanning repository tests, include both runtime tests and compile-time static
tests:

- `test/`
- `static_test/`

## Static Test Style

`static_test/` contains compile-time tests. Add or update these tests when a
behavior can be checked with `static_assert`, `constexpr`, or `consteval`.

- Mirror the production header path where practical. For example,
  `include/usagi/geometry/size/size.hpp` is covered by
  `static_test/geometry/size/size.cpp`.
- Do not use GoogleTest in `static_test/`; use `static_assert` directly.
- Wrap helper types, helper functions, and assertions in an anonymous namespace.
- For multi-step checks, prefer a `static_assert` on a `constexpr` or
  `consteval` lambda that returns `true`.
- Include only the headers needed by the compile-time check.
- Keep runtime behavior checks in `test/`; keep concept, type trait, and
  constant-expression checks in `static_test/`.

## Doxygen Comment Style

When adding or changing public API in `include/`, add or update Doxygen comments
at the same time.

- Use `///` comments for concise API descriptions.
- Document template parameters with `@tparam` when the constraint is part of the
  API contract.
- Document function inputs and outputs with `@param` and `@return`; omit them
  only for trivial default constructors or aliases where there is no meaningful
  input or output to describe.
- Prefer documenting externally visible behavior, invariants, and preconditions
  over implementation details.
- Keep comments synchronized with `static_test/` examples when compile-time
  behavior is part of the contract.

## UI Coordinate And Drawing Specification

When changing UI coordinate conversion, view transform order, draw offsets,
event positions, or clipping behavior, update both:

- `include/usagi/ui/AGENTS.md`
- `docs/ui-coordinate-and-drawing.md`

Keep README examples consistent with those specifications when they mention
`frame()`, `bounds()`, `offset`, gestures, transforms, or clipping.
