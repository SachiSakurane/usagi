#include <type_traits>

#include <usagi/tuple/front.hpp>

namespace {
static_assert(std::is_same_v<void, usagi::tuple::back<std::tuple<int, bool, void>>::type>);
} // namespace
