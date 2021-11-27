#include <usagi/tuple/erase.hpp>

namespace {
static_assert(std::is_same_v<std::tuple<bool, void>,
                             usagi::tuple::erase<0, std::tuple<int, bool, void>>::type>);
static_assert(std::is_same_v<std::tuple<int, bool>,
                             usagi::tuple::erase<2, std::tuple<int, bool, void>>::type>);
} // namespace
