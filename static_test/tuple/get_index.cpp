#include <usagi/tuple/get_index.hpp>

namespace {
static_assert(usagi::tuple::get_index<int, std::tuple<int>>::value == 0);
static_assert(usagi::tuple::get_index<int, std::tuple<void, bool, float, int>>::value == 3);
static_assert(usagi::tuple::get_index<int, std::tuple<void, int, float, int>>::value == 1);
} // namespace
