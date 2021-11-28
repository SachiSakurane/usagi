#include <usagi/tuple/type_at.hpp>
#include <usagi/utility/eval_assert.hpp>

namespace {
static_assert([]() consteval {
  auto t = std::make_tuple(false, 10, 42.f);
  usagi::utility::eval_true(usagi::tuple::type_at<bool>(t) == false);
  usagi::utility::eval_true(usagi::tuple::type_at<int>(t) == 10);
  usagi::utility::eval_true(usagi::tuple::type_at<float>(t) == 42.f);
  return true;
}());
}