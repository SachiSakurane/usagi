#include <type_traits>

#include <usagi/tuple/back.hpp>

namespace {
static_assert(std::is_same_v<void, usagi::tuple::back<std::tuple<int, bool, void>>::type>);
} // namespace
