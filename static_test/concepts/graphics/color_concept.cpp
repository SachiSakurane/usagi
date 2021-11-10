#include <usagi/concepts/graphics/color_concept.hpp>

namespace {
template <class ValueType>
struct Colored {
  using value_type = ValueType;
  value_type red() const;
  value_type green() const;
  value_type blue() const;
  value_type alpha() const;
};

template <class ValueType>
struct UnColored {
  using value_type = ValueType;
  value_type red() const;
  value_type green() const;
  // value_type blue() const;
  value_type alpha() const;
};

static_assert(usagi::concepts::graphics::basic_color_concept<Colored<int>>);
static_assert(!usagi::concepts::graphics::basic_color_concept<UnColored<int>>);
} // namespace