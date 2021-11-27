#include <usagi/tuple/erase.hpp>

namespace {
static_assert(std::is_same_v<std::tuple<bool, void>,
                             usagi::tuple::erase<std::tuple<int, bool, void>, 0>::type>);
static_assert(std::is_same_v<std::tuple<int, bool>,
                             usagi::tuple::erase<std::tuple<int, bool, void>, 2>::type>);
} // namespace
