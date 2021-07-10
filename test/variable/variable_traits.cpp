#include <usagi/variable/variable_traits.hpp>

namespace {
static_assert(std::is_same_v<usagi::variable_traits<float>::value_type, float>);
static_assert(std::is_same_v<usagi::variable_traits<float>::variable_type, usagi::variable<float>>);
} // namespace
