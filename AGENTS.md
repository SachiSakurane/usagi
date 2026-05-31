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
