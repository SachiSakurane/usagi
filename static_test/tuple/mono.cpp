#include <usagi/tuple/mono.hpp>

namespace {
static_assert(std::is_same_v<std::tuple<bool, bool>,
                             usagi::tuple::mono<2, bool>::type>);
static_assert(std::is_same_v<std::tuple<>,
                             usagi::tuple::mono<0, bool>::type>);
} // namespace
