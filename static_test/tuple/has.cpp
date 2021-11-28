#include <usagi/tuple/has.hpp>

namespace {
static_assert(usagi::tuple::has<int, std::tuple<int>>::value);
static_assert(usagi::tuple::has<int, std::tuple<void, bool, float, int>>::value);
static_assert(!usagi::tuple::has<int, std::tuple<void, bool, float>>::value);
} // namespace

