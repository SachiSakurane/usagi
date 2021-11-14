#include <usagi/concepts/is_invocable_f_r_args.hpp>
#include <usagi/ui/gesture.hpp>

namespace {
struct a_tag {};
struct b_tag {};

using void_tuple = std::tuple<void, a_tag, b_tag>;
using bool_tuple = std::tuple<bool, a_tag, b_tag>;

namespace is_apply_invocable_ {
  // SearchArgsTuple と target_tuple が一致
  static_assert(
      usagi::ui::detail::is_apply_invocable<std::function<bool(a_tag, b_tag)>, bool_tuple>(
          std::make_index_sequence<std::tuple_size_v<bool_tuple>>()));

  // SearchArgsTuple と target_tuple が一致
  static_assert(
      usagi::ui::detail::is_apply_invocable<std::function<void(a_tag, b_tag)>, void_tuple>(
          std::make_index_sequence<std::tuple_size_v<void_tuple>>()));

  // SearchArgsTuple と target_tuple が不一致
  static_assert(
      !usagi::ui::detail::is_apply_invocable<std::function<void(a_tag, a_tag)>, void_tuple>(
          std::make_index_sequence<std::tuple_size_v<void_tuple>>()));
} // namespace is_apply_invocable_

namespace pick_func_wrapper_ {
  // SearchArgsTuple と一致する candidates 中から存在し、対象の function を返す
  static_assert(usagi::utility::is_invocable_f_r_args_v<
                decltype(usagi::ui::detail::pick_func_wrapper<void_tuple>(
                    std::declval<std::function<void(a_tag, b_tag)>>())),
                void, a_tag, b_tag>);

  // SearchArgsTuple と一致する複数の candidates 中から存在し、対象の function を返す
  static_assert(usagi::utility::is_invocable_f_r_args_v<
                decltype(usagi::ui::detail::pick_func_wrapper<void_tuple>(
                    std::declval<std::function<void(a_tag, a_tag)>>(),
                    std::declval<std::function<void(b_tag, a_tag)>>(),
                    std::declval<std::function<void(b_tag, b_tag)>>(),
                    std::declval<std::function<void(a_tag, b_tag)>>())),
                void, a_tag, b_tag>);

  // SearchArgsTuple と一致する candidates がないので nullptr
  static_assert(std::is_same_v<decltype(usagi::ui::detail::pick_func_wrapper<void_tuple>(
                                   std::declval<std::function<void(a_tag, a_tag)>>(),
                                   std::declval<std::function<void(b_tag, a_tag)>>(),
                                   std::declval<std::function<void(b_tag, b_tag)>>())),
                               std::nullptr_t>);
} // namespace pick_func_wrapper_

} // namespace
