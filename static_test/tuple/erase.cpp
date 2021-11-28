#include <type_traits>

#include <usagi/tuple/erase.hpp>

namespace {
static_assert(std::is_same_v<std::tuple<bool, void>,
                             usagi::tuple::erase<std::tuple<int, bool, void>, 0>::type>);
static_assert(std::is_same_v<std::tuple<int, bool>,
                             usagi::tuple::erase<std::tuple<int, bool, void>, 2>::type>);
static_assert(std::is_same_v<std::tuple<bool, void>,
                             usagi::tuple::erase_front<std::tuple<int, bool, void>>::type>);
static_assert(std::is_same_v<std::tuple<int, bool>,
                             usagi::tuple::erase_back<std::tuple<int, bool, void>>::type>);
} // namespace
