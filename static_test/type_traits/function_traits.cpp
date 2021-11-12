#include <usagi/type_traits/function_traits.hpp>

namespace {
namespace void_free_function_ {
  void test_func();

  using free_func_type = decltype(test_func);

  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<free_func_type>::result_type, void>);
  static_assert(usagi::type_traits::function_traits<free_func_type>::arity == 0);
  static_assert(std::is_same_v<usagi::type_traits::function_traits<free_func_type>::arguments_tuple,
                               std::tuple<>>);
} // namespace void_free_function_

namespace free_function_ {
  int test_func(bool, float);

  using free_func_type = decltype(test_func);

  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<free_func_type>::result_type, int>);
  static_assert(usagi::type_traits::function_traits<free_func_type>::arity == 2);
  static_assert(std::is_same_v<usagi::type_traits::function_traits<free_func_type>::arguments_tuple,
                               std::tuple<bool, float>>);
  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<free_func_type>::argument_type<0>, bool>);
  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<free_func_type>::argument_type<1>, float>);
} // namespace free_function_

namespace function_pointer_ {
  using test_func = int (*)(bool, float);

  static_assert(std::is_same_v<usagi::type_traits::function_traits<test_func>::result_type, int>);
  static_assert(usagi::type_traits::function_traits<test_func>::arity == 2);
  static_assert(std::is_same_v<usagi::type_traits::function_traits<test_func>::arguments_tuple,
                               std::tuple<bool, float>>);
  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<test_func>::argument_type<0>, bool>);
  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<test_func>::argument_type<1>, float>);
} // namespace function_pointer_

namespace class_member_ {
  struct test_class {
    auto test_func(bool, float) -> int;
  };

  using class_member_type = decltype(&test_class::test_func);

  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<class_member_type>::result_type, int>);
  static_assert(usagi::type_traits::function_traits<class_member_type>::arity == 2);
  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<class_member_type>::arguments_tuple,
                     std::tuple<bool, float>>);
  static_assert(std::is_same_v<
                usagi::type_traits::function_traits<class_member_type>::argument_type<0>, bool>);
  static_assert(std::is_same_v<
                usagi::type_traits::function_traits<class_member_type>::argument_type<1>, float>);
} // namespace class_member_

namespace class_member_const_ {
  struct test_class {
    auto test_func(bool, float) const -> int;
  };

  using class_member_type = decltype(&test_class::test_func);

  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<class_member_type>::result_type, int>);
  static_assert(usagi::type_traits::function_traits<class_member_type>::arity == 2);
  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<class_member_type>::arguments_tuple,
                     std::tuple<bool, float>>);
  static_assert(std::is_same_v<
                usagi::type_traits::function_traits<class_member_type>::argument_type<0>, bool>);
  static_assert(std::is_same_v<
                usagi::type_traits::function_traits<class_member_type>::argument_type<1>, float>);
} // namespace class_member_const_

namespace functor_ {
  auto test_lambda = [](bool, float) { return 1; };
  using lambda_functor_type = decltype(test_lambda);

  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<lambda_functor_type>::result_type, int>);
  static_assert(usagi::type_traits::function_traits<lambda_functor_type>::arity == 2);
  static_assert(
      std::is_same_v<usagi::type_traits::function_traits<lambda_functor_type>::arguments_tuple,
                     std::tuple<bool, float>>);
  static_assert(std::is_same_v<
                usagi::type_traits::function_traits<lambda_functor_type>::argument_type<0>, bool>);
  static_assert(std::is_same_v<
                usagi::type_traits::function_traits<lambda_functor_type>::argument_type<1>, float>);
} // namespace functor_
} // namespace
