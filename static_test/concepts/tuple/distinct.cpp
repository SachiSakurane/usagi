#include <usagi/concepts/tuple/distinct.hpp>

namespace {
static_assert(usagi::concepts::tuple::distinct<std::tuple<int, float, void, double, char>>);
static_assert(!usagi::concepts::tuple::distinct<std::tuple<int, float, void, double, int>>);
}
