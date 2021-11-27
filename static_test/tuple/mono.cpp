#include <usagi/tuple/mono.hpp>

namespace {
static_assert(std::is_same_v<std::tuple<bool, bool>,
                             usagi::tuple::mono<bool, 2>::type>);
static_assert(std::is_same_v<std::tuple<>,
                             usagi::tuple::mono<bool, 0>::type>);
} // namespace
